#include "ResponseGet.hpp"

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
	std::string head = createHead(request->getData().header);
	std::string body = createBody(request->getData().body);
	_dataToSend = head + body;
//	TODO delete hardcode
//	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 436\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><form method='POST' action='127.0.0.1'><input name='value' value='key' placeholder='TEST'><button>POST</button></form><script src='index.js'></script></body></html>";
//	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><script src='index.js'></script></body></html>";
	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
	_leftBytesToSend = _dataToSend.length();

}

ResponseGet::~ResponseGet() {}

std::string ResponseGet::createHead(const requestHeaderStruct& headers){
	requestHeaderStruct::const_iterator it;
	std::cout << "HEAD" << std::endl;
//	handle_method(headers.find("method"));
//	handle_host(headers.find("host"));
//	handle_location(headers.find("location"));
	for (it = headers.begin(); it != headers.end(); it++)//TODO optimeze all header methods in one loop
	{

	}
	return "";
}

std::string ResponseGet::createBody(const std::string& body) {
	std::cout << "BODY" << std::endl;

	std::cout << "Body: " << std::endl << body << std::endl;
	return "";
}
