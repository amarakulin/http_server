#include "Response.hpp"

const t_response_process Response::_arrProcessHeaders[] = {
		{.nameHeader = "uri", .getProcessedHeader = getContentLengthHeader },
		{.nameHeader = "accept", .getProcessedHeader = getContentTypeHeader },
		{.nameHeader = "", .getProcessedHeader = nullptr},

		};

Response::Response() {
	_state = NO_RESPONSE;
	_leftBytesToSend = 0;
}

Response::Response(const Response& other) {
	operator=(other);
}

Response::Response(RequestData &requestData, HostData *hostData)
{
	_status = 0;
	createHead(requestData, hostData);
}

Response &Response::operator=(const Response &assign){
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

Response::~Response() {}



bool Response::isDone(){
	return _state == SENDED;
}

void Response::countSendedData(int byteSended){
	if (byteSended < 0 || byteSended > _leftBytesToSend){
		//TODO may be 500;
		std::cout << "DATA SENT is negative!!!" << std::endl;
	}
	_leftBytesToSend -= byteSended;
	if (_leftBytesToSend == 0 && !_dataToSend.empty()){
		_state = SENDED;
	}
	_dataToSend.erase(_dataToSend.begin(), _dataToSend.begin() + byteSended);
}

void Response::createHead(RequestData &requestData, HostData *hostData)
{
	_state = SENDING;
	requestHeaderStruct headers = requestData.header;
	requestHeaderStruct::const_iterator it;
	for (it = headers.begin(); it != headers.end(); it++){
		_dataToSend += processHeader(it->first, it->second, hostData);
	}
	_dataToSend += createRedirectHeader(headers["uri"], hostData);
	_dataToSend = createHeadHeader() + _dataToSend;
}

void Response::createBody(const std::string &uri, HostData *hostData)
{
	std::string filename = getFilePathFromHostData(uri, hostData);
	std::string body = getDataFileAsString(filename);
	_dataToSend += "\r\n";
	_dataToSend += body;
}

std::string Response::processHeader(const std::string &headerName,
									const std::string &headerValue,
									HostData *hostData)
{
	std::string processedStrHeader = "";

	for (int i = 0; _arrProcessHeaders[i].getProcessedHeader; i++){
		if (_arrProcessHeaders[i].nameHeader == headerName){
			processedStrHeader = _arrProcessHeaders[i].getProcessedHeader(headerValue, hostData);
			break;
		}
	}
	if (!processedStrHeader.empty()){
		processedStrHeader += "\r\n";
	}

	return processedStrHeader;
}

std::string Response::createHeadHeader(){
	if (!_status){
		_status = STATUS_OK;
	}
	std::string processedStr = VERSION_HTTP;
	processedStr += std::to_string(_status);
	for (int i = 0; arrResponseStatuses[i].first ; i++){
		if (arrResponseStatuses[i].first == _status){
			processedStr += " " + arrResponseStatuses[i].second;
			break;
		}
	}
	processedStr += "\r\n";
	return processedStr;
}

std::string
Response::getContentTypeHeader(std::string accept, HostData *hostData)
{
	std::string processedStr = CONTENT_TYPE;
	long found = static_cast<long> (accept.find(','));
	if (found != std::string::npos){
		accept.erase(accept.begin() + found, accept.end());
	}
	processedStr += accept;
	return processedStr;
}

std::string
Response::getContentLengthHeader(std::string uri, HostData *hostData)
{
	std::string processedStr = CONTENT_LENGTH;

	std::string filename = getFilePathFromHostData(uri, hostData);
	long sizeFile = getSizeFile(filename);
	if (sizeFile == -1){
		std::cout << "[-] Error can't count size file: " << filename << std::endl;
		//TODO gonna 404 worked out before
	}
	processedStr += std::to_string(sizeFile);
	return processedStr;
}

std::string
Response::createRedirectHeader(const std::string &uri, HostData *hostData)
{
	std::string processedStr = "";
	Location *location = getLocationByUri(uri, hostData->location);

	if (location && !location->redirectPath.empty()){
		_status = static_cast<int> (location->redirectStatusCode);
		processedStr = LOCATION;
		processedStr += location->redirectPath;
		processedStr += "\r\n";
	}
	return processedStr;
}

void Response::changeContentLength(size_t valueContentLength){
	std::string search = CONTENT_LENGTH;
	size_t pos = _dataToSend.find(search);
	if (pos == std::string::npos){
		return;
	}
	pos += search.length();
	std::string::iterator itStart = _dataToSend.begin() + static_cast<long>(pos);
	std::string::iterator itEnd = itStart;
	std::string oldValueContentLength;
	for (; *itEnd != std::string::npos && *itEnd != '\r' ; ++itEnd ){
		oldValueContentLength += *itEnd;
	}
	_dataToSend.replace(pos, oldValueContentLength.length(), std::to_string(valueContentLength));
}

std::string
Response::getFilePathFromHostData(const std::string &uri, HostData *hostData){
	std::string filePath;
	std::vector<std::string> index;
	std::string root = "";
	Location *location = nullptr;

	std::vector<Location*> vectorLocations = hostData->location;
	location = getLocationByUri(uri, hostData->location);
	if (location){//TODO refactor
		root = location->root;
		index = location->index;
	}
	if (root.empty()){
		root = hostData->root;
	}
	filePath = "." + root + uri;
	for (size_t i = 0; i < index.size(); ++i){//TODO unique function
		if (isFileExist(filePath + "/" + index[i])){
			filePath += "/" + index[i];
			break;
		}
	}
	if (location && location->autoindex && !isFileExist(filePath)){
		generatePageAutoindex(filePath, uri, hostData);
		//TODO autoindex
		// search for a childs locations and files all files form current directory
		// back locations ? -> is parent uri location
		filePath += "/autoindex.html";
	}
	return filePath;
}

bool compareLocations(Location* loc1, Location* loc2){
	return loc1->way.size() < loc2->way.size();
}

Location *Response::getLocationByUri(const std::string &uri, std::vector<Location*> locations){
	Location *location = nullptr;// DANGER GONNA MAKE A BEHAVIOR IF NOT FIND A LOCATION!!!
	size_t matchPos = std::string::npos;
	std::string matchStr;
	std::string extensionOfUriFile;
	std::string lastMatch = "";
	bool isExtensionLocation;

	extensionOfUriFile = getExtensionFileFromUri(uri);
	std::sort(locations.begin(), locations.end(), compareLocations);
	for (size_t i = 0; i < locations.size(); ++i){
		matchStr = uri.substr(0, locations[i]->way.size());
		matchPos = locations[i]->way.find(matchStr);
		isExtensionLocation = !extensionOfUriFile.empty()
								&& extensionOfUriFile == getExtensionFileFromUri(locations[i]->way)
								&& locations[i]->way.find('*') != std::string::npos;

		if (matchPos != std::string::npos && lastMatch != matchStr){
			location = locations[i];
			lastMatch = matchStr;//if uri is -> '/' when gets last location
		}
		else if (isExtensionLocation){
			location = locations[i];
			break;
		}
	}
	return location;
}

std::string Response::getUploadFilePath(Location *location){//TODO move up to Response
	std::string uploadPath;
	if (location && location->uploadEnable){
		uploadPath = location->root + location->uploadPath;
	}
	if (uploadPath.empty()) {
		uploadPath = DEFAULT_UPLOAD_PATH;
	}
	uploadPath += "/";
	return uploadPath;
}

std::string Response::getFileNameFromUri(const std::string &uri){
	std::string filename = "";
	size_t posFile = uri.find_last_of('/');
	if (posFile != std::string::npos){
		posFile += 1;// to delete '/'
		filename = uri.substr(posFile, uri.size() - posFile);
	}
	return filename;
}

std::string Response::getExtensionFileFromUri(const std::string &uri){
	std::string filename;
	size_t posExtension;
	std::string fileExtension = "";

	filename = getFileNameFromUri(uri);
	posExtension = filename.find('.');
	if (posExtension != std::string::npos){
		fileExtension = filename.substr(posExtension, filename.size() - posExtension);
	}
	return fileExtension;
}


void Response::generatePageAutoindex(std::string filePath, const std::string &uri, HostData *hostData){
	std::string contentFile = "";
	std::string tmpRef;
	std::vector<std::string> listDir = listOfFiles(filePath);
	contentFile += "<!DOCTYPE html>\n"
				   "<html lang=\"en\">\n"
				   "<head>\n"
				   "    <meta charset=\"UTF-8\">\n"
				   "    <title>Title</title>\n"
				   "    <style>\n"
				   "        body{\n"
				   "            background-color: #606060;\n"
				   "            color: #FFFFFF;/* Цвет фона веб-страницы */\n"
				   "        }\n"
				   "    </style>\n"
				   "</head>\n"
				   "<body>";
	for (int i = 0; i < listDir.size(); ++i){
		tmpRef = "<p><a href='" + listDir[i] + "'>";
		contentFile += tmpRef;
		contentFile += listDir[i];
		contentFile += "</a></p>";
	}
	contentFile += "</body></html>";
	std::cout << "Content: "<< contentFile << std::endl;
	filePath += "/autoindex.html";
	std::ofstream outfile (filePath);
	outfile << contentFile << std::endl;
	outfile.close();
}

/*
** Getters
*/

size_t Response::getLeftBytesToSend() const {
	return _leftBytesToSend;
}

const std::string &Response::getDataToSend() const{
	return _dataToSend;
}

int Response::getStatus() const {
	return _status;
}

int Response::getState() const{
	return _state;
}

/*
** Setters
*/
