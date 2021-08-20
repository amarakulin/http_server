#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _buffer() {}

Request::Request(const Request& other)
	: _status(other._status), _buffer(other._buffer) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_buffer += chunk;

	std::transform(_buffer.begin(), _buffer.end(), _buffer.begin(), ::tolower);
	
	if (isDone()) {
		_status = READED;
	} else {
		_status = READING;
	}
}

bool		Request::isDone() {
	// if (_sup.method == "GET" || _sup.method == "DELETE") {
	if (_buffer.find("\r\n\r\n") == std::string::npos)
		return false;
	// } else if (_sup.method == "POST") {
		
	// }
	return true;
}

void		Request::resetRequest() {
	_status = NO_REQUEST;
	_buffer = "";
	_data.header.empty();
	_data.body = "";
}

/*
** Getters
*/

int			Request::getStatus() const {
	return _status;
}

std::string	Request::getMethod() {
	return _data.header["method"];
}

RequestData& Request::getData() {
	return _data;
}