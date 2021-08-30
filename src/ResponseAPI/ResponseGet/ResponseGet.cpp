#include "ResponseGet.hpp"


ResponseGet::ResponseGet() : Response() {}

ResponseGet::ResponseGet(const ResponseGet& other) : Response(other) {}

ResponseGet &ResponseGet::operator=(const ResponseGet &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponseGet::ResponseGet(RequestData& requestData) : Response(requestData) {
	createBody(requestData);
//	TODO delete hardcode
//	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 436\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><form method='POST' action='127.0.0.1'><input name='value' value='key' placeholder='TEST'><button>POST</button></form><script src='index.js'></script></body></html>";
//	_dataToSend = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><script src='index.js'></script></body></html>";
//	std::string a = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
//	std::cout << "$$$$$ DATA TO SEND: " << "|" <<_dataToSend << "|" << std::endl;
//	std::cout << "$$$$$ AAAA TO SEND: " << "|"  << a << "|" << std::endl;

	_leftBytesToSend = _dataToSend.length();

}

ResponseGet::~ResponseGet() {}

void ResponseGet::createBody(RequestData& requestData) {
	std::string filename = requestData.header.find("uri")->second;
	filename = filename;
	if (filename == "./"){//TODO needs to know default List<file> if directory is given from config
		filename += "index.html";
	}
//	std::cout << "filename body: " << filename << std::endl;
	std::string body = getDataFileAsString(filename);
//	std::cout << "Body: " << body << std::endl;
	_dataToSend += "\r\n";
	_dataToSend += body;
}
