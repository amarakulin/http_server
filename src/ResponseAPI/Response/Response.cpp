#include "Response.hpp"

const t_response_process Response::_arrProcessHeaders[] = {
		{.nameHeader = "method", .getProcessedHeader = getProcessedMethod },
		{.nameHeader = "host", .getProcessedHeader = getProcessedHost },
		{.nameHeader = "location", .getProcessedHeader = getProcessedLocation },
		{.nameHeader = "protocol", .getProcessedHeader = getProcessedProtocol },
		{.nameHeader = "accept", .getProcessedHeader = getProcessedAccept },
		{.nameHeader = "", .getProcessedHeader = nullptr},

		};

Response::Response() {
	_state = NO_RESPONSE;
	_leftBytesToSend = 0;//TODO Think
}

Response::Response(const Response& other) {
	operator=(other);
}

Response::Response(Request *request) {
	createHead(request);
	_state = SENDING;
}

Response &Response::operator=(const Response &assign){
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getStatus();
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

void Response::createHead(Request *request){
	requestHeaderStruct headers = request->getData().header;
	requestHeaderStruct::const_iterator it;
	std::cout << "HEAD" << std::endl;
	std::string head = createHeadHeader("status");
	_dataToSend = head + _dataToSend;
	_dataToSend += createContentLengthHeader(headers.find("location")->second);
	for (it = headers.begin(); it != headers.end(); it++){
		_dataToSend += processHeader(it->first, it->second);
	}
}


std::string Response::processHeader(const std::string &headerName, const std::string &headerValue){
	std::cout << headerName << " : " << headerValue << std::endl;
	std::string processedStrHeader = "";
	for (int i = 0; _arrProcessHeaders[i].getProcessedHeader; i++){
		if (_arrProcessHeaders[i].nameHeader == headerName){
			processedStrHeader = _arrProcessHeaders[i].getProcessedHeader(headerValue);
			break;
		}
	}
	if (!processedStrHeader.empty()){
		processedStrHeader += "\r\n";
	}

	return processedStrHeader;
}

std::string Response::getProcessedMethod(std::string method){
	return "";
}

std::string Response::getProcessedHost(std::string host){
	return "";
}

std::string Response::getProcessedLocation(std::string location){
	return "";
}

std::string Response::getProcessedProtocol(std::string protocol){
	return "";
}

std::string Response::createContentLengthHeader(std::string location){
	std::string processedStr = "Content-length: ";
	// TODO find location
	// Count lenght of the file
	// Add the lenght to the string;
	location = "/Users/tilda/http_server/index.html";
	long sizeFile = getSizeFile(location);
	if (sizeFile == -1){
		std::cout << "[-] Error can't count size file" << std::endl;
		//TODO throw exception
	}
	processedStr += std::to_string(sizeFile);
	processedStr += "\r\n";// TODO change hardcode
	return processedStr;
}

std::string Response::createHeadHeader(std::string status){
	return "HTTP/1.1 200 OK\r\n";
}

std::string Response::getProcessedAccept(std::string accept){
	std::string processedStr = "Content-type: ";//TODO handle Accept-Charset here
	long found = static_cast<long> (accept.find(','));
	if (found != std::string::npos){
		accept.erase(accept.begin() + found, accept.end());
	}
	processedStr += accept;
	return processedStr;
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
	return _state;
}

/*
** Setters
*/
