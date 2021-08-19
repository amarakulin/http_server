#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _data(), _sup() {}

Request::Request(const Request& other)
	: _status(other._status), _data(other._data), _sup() {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_data += chunk;

	std::transform(_data.begin(), _data.end(), _data.begin(), ::tolower);
	
	if (!_sup.method.length())
		parseMethod();

	if (!_sup.contentLenght)
		parseContentLength();

	if (isDone()) {
		_status = READED;
	} else {
		_status = READING;
	}
}

void		Request::parseContentLength() {
	std::stringstream 	ss;  
	std::string			searchString = "content-length: ";
	size_t 				index = _data.find(searchString);

	if (index != std::string::npos) {
		ss << _data.c_str() + (index + searchString.length());
		ss >> _sup.contentLenght;
	}
}

void		Request::parseMethod() {
	if (_data.find("get") != std::string::npos)
		_sup.method = "GET";
	else if (_data.find("post") != std::string::npos)
		_sup.method = "POST";
	else if (_data.find("delete") != std::string::npos)
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

/*
** Getters
*/

int			Request::getStatus() const {
	return _status;
}

std::string	Request::getMethod() const {
	return _sup.method;
}

RequestReadingData Request::getReadingData() const {
	return _sup;
}