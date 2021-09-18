#include "ResponsePost.hpp"

ResponsePost::ResponsePost() : Response() {}

ResponsePost::ResponsePost(const ResponsePost& other) : Response(other) {
	operator=(other);
}

ResponsePost &ResponsePost::operator=(const ResponsePost &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponsePost::ResponsePost(RequestData &requestData, HostData *hostData)
	: Response(requestData, hostData) {
	ResponsePost::createBody(requestData, hostData);

	std::cout << "B LeftBytes: " << _leftBytesToSend  << std::endl;
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
	std::cout << "A LeftBytes: " << _leftBytesToSend  << std::endl;
}

ResponsePost::~ResponsePost() {}

std::pair<std::string, std::string> ResponsePost::parseBody(std::string body){
	size_t filenameOffset;
	std::pair<std::string, std::string> bodyStruct;
	std::string filenameSeporator = FILENAME_SEPORATOR;

	size_t file_end = body.find(filenameSeporator, 0);
	if (file_end != std::string::npos){
		filenameOffset = file_end + filenameSeporator.length();
		bodyStruct.first = body.substr(0, file_end);
		bodyStruct.second = body.substr(filenameOffset, body.length() - filenameOffset);
	}
	else{
		bodyStruct.first = "";
		bodyStruct.second = body;
	}
	return bodyStruct;
}



void ResponsePost::createBody(RequestData &requestData, HostData *hostData){
	std::pair<std::string, std::string> bodyStruct;
	std::string filePath;
	std::string dataFromCGI;
	Location *location;

	bodyStruct = parseBody(requestData.body);//TODO may be needs a constuctor with size
	location = getLocationByUri(requestData.header["uri"], hostData->location);
	std::cout << BLUE << "FilenameFromUri: " << getFileNameFromUri(requestData.header["uri"]) << RESET << std::endl;
	if (bodyStruct.first.empty()){
		bodyStruct.first = getFileNameFromUri(requestData.header["uri"]);
	}
	filePath = "." + getUploadFilePath(location) + bodyStruct.first;

//TODO test chunked method
	std::ofstream outfile (filePath);
	if (!isFileExist(filePath)){
		//TODO if throw exception could lose the pointer on the response
//		throw NotFoundException();
	}

	outfile << bodyStruct.second << std::endl;
	outfile.close();
	// Response::createBody(requestData.header["uri"], hostData);


	if (!isBoundaryBody(requestData.header) && (location && location->cgi) && requestData.body != "") {
		requestData.header["content-length"] = std::to_string(requestData.body.length());

		std::cout << BOLDRED << "Before execute cgi" << RESET << std::endl;
		dataFromCGI = location->cgi->execute(requestData);
		dataFromCGI = getDataFileAsString("./cgi/cgi_out");
		dataFromCGI.erase(0, dataFromCGI.find("\r\n\r\n") + 4);
		changeContentLength(dataFromCGI.size());
	} else {
		Response::createBody(requestData.header["uri"], hostData);
		return;
	}
	_dataToSend += "\r\n";
	_dataToSend += dataFromCGI;
}

void ResponsePost::createBody(const std::string &uri, HostData *hostData){
	Response::createBody(uri, hostData);
}

bool	ResponsePost::isBoundaryBody(requestHeaderStruct header) {
	requestHeaderStruct::iterator end = header.end();
	std::string contentType = header["content-type"];

	if (header.find("content-type") != end && contentType.find("boundary") == std::string::npos)
		return false;
	else if (header.find("content-type") == end)
		return false;
	return true;
}
