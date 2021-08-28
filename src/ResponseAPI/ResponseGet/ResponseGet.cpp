#include "ResponseGet.hpp"

const t_response_process ResponseGet::_arrProcessHeaders[] = {
		{.nameHeader = "method", .getProcessedHeader = getProcessedMethod },
		{.nameHeader = "host", .getProcessedHeader = getProcessedHost },
		{.nameHeader = "location", .getProcessedHeader = getProcessedLocation },
		{.nameHeader = "protocol", .getProcessedHeader = getProcessedProtocol },
		{.nameHeader = "accept", .getProcessedHeader = getProcessedAccept },
		{.nameHeader = "", .getProcessedHeader = nullptr},

};

ResponseGet::ResponseGet() : Response() {}

ResponseGet::ResponseGet(const ResponseGet& other) : Response(other) {}

ResponseGet &ResponseGet::operator=(const ResponseGet &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getStatus();
	}
	return *this;
}

ResponseGet::ResponseGet(Request *request) : Response(request) {
	std::string body = "Hello world";
	createHead(request, body);
	createBody(body);
//	TODO delete hardcode
//	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 436\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><form method='POST' action='127.0.0.1'><input name='value' value='key' placeholder='TEST'><button>POST</button></form><script src='index.js'></script></body></html>";
//	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><script src='index.js'></script></body></html>";
//	std::string a = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
	std::cout << "$$$$$ DATA TO SEND: " << "|" <<_dataToSend << "|" << std::endl;
//	std::cout << "$$$$$ AAAA TO SEND: " << "|"  << a << "|" << std::endl;

	_leftBytesToSend = _dataToSend.length();

}

ResponseGet::~ResponseGet() {}

void ResponseGet::createHead(Request *request, const std::string& body){
	requestHeaderStruct headers = request->getData().header;
	requestHeaderStruct::const_iterator it;
	std::cout << "HEAD" << std::endl;

	for (it = headers.begin(); it != headers.end(); it++){
		_dataToSend += processHeader(it->first, it->second);
	}
	std::string head = createHeadHeader("status");
	_dataToSend += createContentLengthHeader(body);
	_dataToSend = head + _dataToSend;
}

void ResponseGet::createBody(const std::string& body) {

	std::cout << "Body: " << body << std::endl;
	_dataToSend += "\r\n";
	_dataToSend += body;
}

std::string ResponseGet::processHeader(const std::string &headerName, const std::string &headerValue){
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
//"HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
std::string ResponseGet::getProcessedMethod(std::string method){
	return "";
}

std::string ResponseGet::getProcessedHost(std::string host){
	return "";
}

std::string ResponseGet::getProcessedLocation(std::string location){
	return "";
}

std::string ResponseGet::getProcessedProtocol(std::string protocol){
//	return "Date: Wed, 21 Oct 2015 07:28:00 GMT";
	return "";
}

std::string ResponseGet::createContentLengthHeader(std::string body){
	std::string processedStr = "Content-length: ";
	processedStr += std::to_string(body.length());
	processedStr += "\r\n";// TODO change
	return processedStr;
}

std::string ResponseGet::createHeadHeader(std::string status){
	return "HTTP/1.1 200 OK\r\n";
}

std::string ResponseGet::getProcessedAccept(std::string accept){
	std::string processedStr = "Content-type: ";//TODO handle Accept-Charset here
	long found = static_cast<long> (accept.find(','));
	if (found != std::string::npos){
		accept.erase(accept.begin() + found, accept.end());
	}
	processedStr += accept;
	return processedStr;

}
