#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _data(), _sup() {}

Request::Request(const Request& other)
	: _status(other._status), _data(other._data), _sup() {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_data += chunk;
	
	if (!_sup.method.length())
		parseMethod();

	if (isDone()) {
		_status = READED;
	} else {
		_status = READING;
	}
}

void		Request::parseMethod() {
	if (_data.find("GET") != std::string::npos)
		_sup.method = "GET";
	else if (_data.find("POST") != std::string::npos)
		_sup.method = "POST";
	else if (_data.find("DELETE") != std::string::npos)
		_sup.method = "DELETE";
}

bool		Request::isDone() {
	if (_sup.method == "GET" || _sup.method == "DELETE") {
		if (_data.find("\r\n\r\n") == std::string::npos)
			return false;
	} else if (_sup.method == "POST") {
		
	}
	return true;
}

void		Request::resetRequest() {
	_status = NO_REQUEST;
	_data = "";
	_sup.method = "";
}

int			Request::getStatus() const {
	return _status;
}

std::string	Request::getMethod() const {
	return _sup.method;
}