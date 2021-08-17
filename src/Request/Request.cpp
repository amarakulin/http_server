#include "Request.hpp"

Request::Request() : _status(READING), _data() {}

Request::Request(const Request& other) {
	*this = other;
}

Request::~Request() {}

void	Request::addRequestChunk(std::string chunk) {
	_data += chunk;
	// isDone();
}

bool	Request::isDone() {
	if (_data.find("\r\n\r\n") != std::string::npos)
		return false;

	// _status = DONE;
	return true;
}

// int		Request::getStatus() const {
// 	return _status;
// }