#include "Request.hpp"

Request::Request() : _data() {
	// std::cout << "			REQUEST			" << std::endl;	
}

Request::Request(const Request& other) : _data(other._data) {}

Request::~Request() {}

void	Request::addRequestChunk(std::string chunk) {
	// _data += chunk;
	_data.insert(_data.length(), chunk);
	std::cout << "|" << _data << "|" << std::endl;
	// isDone();
}

bool	Request::isDone() {
	if (_data.find("\r\n\r\n") == std::string::npos)
		return false;

	// _status = DONE;
	return true;
}

// int		Request::getStatus() const {
// 	return _status;
// }