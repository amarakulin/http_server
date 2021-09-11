#include "Response.hpp"

const t_response_process Response::_arrProcessHeaders[] = {
		{.nameHeader = "uri", .getProcessedHeader = getContentLengthHeader },
		{.nameHeader = "accept", .getProcessedHeader = getContentTypeHeader },
		{.nameHeader = "", .getProcessedHeader = nullptr},

		};

Response::Response() {
	_state = NO_RESPONSE;
	_leftBytesToSend = 0;//TODO Think
}

Response::Response(const Response& other) {
	operator=(other);
}

Response::Response(RequestData &requestData, HostData *hostData)
{
	_status = 0;
	std::cout << "Response Constructor" << std::endl;
	std::cout << "Port: "<< hostData->port << std::endl;
	std::cout << "Root: " << hostData->root << std::endl;
	std::cout << "Host: " <<  hostData->host << std::endl;
	std::cout << "ServName: "<< hostData->serverName << std::endl;
//	std::cout << hostData->location[0]->way << std::endl;

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
	std::cout << "REQUEST" << std::endl;

	for (it = headers.begin(); it != headers.end(); it++){

		_dataToSend += processHeader(it->first, it->second, hostData);
	}
//	_dataToSend = createRedirectHeader(hostData);
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
			std::cerr << headerName << " : " << headerValue << std::endl;
			processedStrHeader = _arrProcessHeaders[i].getProcessedHeader(headerValue, hostData);
			break;
		}
	}
	if (!processedStrHeader.empty()){
		processedStrHeader += "\r\n";
	}

	return processedStrHeader;
}

std::string Response::createHeadHeader(){//TODO think if got a error(5xx) while creating body. How to change 'head'?
	//TODO if redirect 3xx
	//TODO if client error 4xx
	//TODO if server error 5xx
	//TODO if ok 2xx
	if (!_status){
		_status = 200;//TODO may be different 2xx
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
	std::string processedStr = CONTENT_TYPE;//TODO handle Accept-Charset here
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
		std::cout << "[-] Error can't count size file" << std::endl;
		//TODO throw exception may be
	}
	processedStr += std::to_string(sizeFile);
	return processedStr;
}

std::string Response::createRedirectHeader(HostData *hostData){
	std::string processedStr = LOCATION;
	processedStr += "";//TODO add a location form Config
	processedStr += "\r\n";
//	_status = 300;//TODO add a location form Config
	return "";
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
	Location *tmpLocation;
	std::string filePath = hostData->root + uri;
	std::cerr << "Uri: " << uri << std::endl;
	std::string filename = uri.substr(uri.find_last_of("/\\") + 1);
	std::cerr << "Filename: " << filename << std::endl;
	std::cerr << "FilePath: " << filePath << std::endl;
	if ( filename.find('.') != std::string::npos){
		return "." + filePath;//TODO refactor
	}
	for(size_t i = 0; i < hostData->location.size(); ++i){
		tmpLocation = hostData->location[i];
		if ((tmpLocation->way + tmpLocation->root) == filePath){
			break;
		}
	}
	filePath = "." + filePath;//TODO refactor
	for (size_t i = 0; i < tmpLocation->index.size(); ++i){
		if (isFileExist(filePath + tmpLocation->index[i])){
			filePath += tmpLocation->index[i];
			break;
		}
	}
	return filePath;
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
