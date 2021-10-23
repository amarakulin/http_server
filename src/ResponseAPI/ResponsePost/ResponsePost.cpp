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

	_leftBytesToSend = _dataToSend.length();
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

	bodyStruct = parseBody(requestData.body);
	location = getLocationByUri(requestData.header["uri"], hostData->location);
	if (bodyStruct.first.empty()){
		bodyStruct.first = getFileNameFromUri(requestData.header["uri"]);
	}
	filePath = "." + getUploadFilePath(location) + bodyStruct.first;

	std::ofstream outfile (filePath);

	outfile << bodyStruct.second << std::endl;
	outfile.close();


	if (!isBoundaryBody(requestData.header) && (location && location->cgi) && requestData.body != "") {
		requestData.header["content-length"] = std::to_string(requestData.body.length());

		dataFromCGI = location->cgi->execute(requestData);
		changeContentLength(dataFromCGI.size());
	} else {
		dataFromCGI = bodyStruct.second;
		changeContentLength(dataFromCGI.size());
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
