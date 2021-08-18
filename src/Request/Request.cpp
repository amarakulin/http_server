#include "Request.hpp"

Request::Request() : _status(NO_REQUEST), _data() {}

Request::Request(const Request& other) : _data(other._data) {}

Request::~Request() {}

void	Request::addRequestChunk(std::string chunk) {
	_data += chunk;
	
	if (isDone())
		_status = DONE;
	else
		_status = READING;
}

bool	Request::isDone() {
	if (_data.find("\r\n\r\n") == std::string::npos)
		return false;
	return true;
}

void	Request::resetRequest() {
	_status = NO_REQUEST;
	_data = "";
}

Request *Request::clone() const{
	return (new Request(*this));
}

int		Request::getStatus() const {
	return _status;
}