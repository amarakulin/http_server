#include "Request.hpp"

Request::Request() : _status(NO_REQUEST), _data() {}

Request::Request(const Request& other) : _data(other._data) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_data += chunk;
	
	if (isDone()) {
		_status = READED;
		parseMethod();
	} else {
		_status = READING;
	}
}

void		Request::parseMethod() {
	if (_data.find("GET") != std::string::npos)
		_method = "GET";
	else if (_data.find("POST") != std::string::npos)
		_method = "POST";
	else if (_data.find("DELETE") != std::string::npos)
		_method = "DELETE";
}

bool		Request::isDone() {
	if (_data.find("\r\n\r\n") == std::string::npos)
		return false;
	return true;
}

void		Request::resetRequest() {
	_status = NO_REQUEST;
	_data = "";
	_method = "";
}

int			Request::getStatus() const {
	return _status;
}

std::string	Request::getMethod() const {
	return _method;
}