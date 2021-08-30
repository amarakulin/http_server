#include "Response.hpp"
# include "ResponseError.hpp"

const t_response_process Response::_arrProcessHeaders[] = {
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

Response::Response(RequestData& requestData) {
	_status = 0;
	createHead(requestData);
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

void Response::createHead(RequestData& requestData){
	_state = SENDING;
	requestHeaderStruct headers = requestData.header;
	requestHeaderStruct::const_iterator it;
//	std::string head = createHeadHeader();
//	_dataToSend = head + _dataToSend;
	_dataToSend += createContentLengthHeader(headers.find("uri")->second);
	for (it = headers.begin(); it != headers.end(); it++){
		_dataToSend += processHeader(it->first, it->second);
	}
	_dataToSend = createHeadHeader() + _dataToSend;
}


std::string Response::processHeader(const std::string &headerName, const std::string &headerValue){
//	std::cout << headerName << " : " << headerValue << std::endl;
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


std::string Response::createContentLengthHeader(std::string uri){
	std::string processedStr = "Content-length: ";
	std::string filename = uri;

	if (filename == "./"){//TODO needs to know default List<file> if directory is given from config
		filename += "index.html";
	}
//	std::cout << "filename: " << filename << std::endl;
	long sizeFile = getSizeFile(filename);
	if (sizeFile == -1){
		std::cout << "[-] Error can't count size file" << std::endl;
		//TODO throw exception
	}
	processedStr += std::to_string(sizeFile);
	processedStr += "\r\n";// TODO change hardcode
	return processedStr;
}

std::string Response::createHeadHeader(){//TODO think if got a error(5xx) while creating body. How to change 'head'?
	//TODO if redirect 3xx
	//TODO if client error 4xx
	//TODO if server error 5xx
	//TODO if ok 2xx
	processStatus();
	std::string processedStr = "HTTP/1.1 ";
	processedStr += std::to_string(_status);
	//TODO go throught loop with all status codes to get a string after given status
	if (_status < 300){
		processedStr += " OK";
	}
	else if (_status < 400){
		processedStr += " Redirect";
	}
	else if (_status < 500){
		processedStr += " Bad Request";
	}
	else {
		processedStr += " Internal Server Error";
	}
	processedStr += "\r\n";
	return processedStr;
}

void Response::processStatus(){
	if (_status){//Already 3xx or 4xx or 5xx
		return;
	}
	if (typeid(this) == typeid(ResponseError)){
		_status = 400;
	}
	else {
		_status = 200;
	}
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
	return _status;
}

int Response::getState() const{
	return _state;
}

void Response::setStatus(int status){
	_status = status;
}


/*
** Setters
*/
