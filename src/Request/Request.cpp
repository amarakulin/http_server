#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _buffer() {}

Request::Request(const Request& other)
	: _status(other._status), _buffer(other._buffer) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_buffer += chunk;

	handleEndOfHeader();
	
	if (isDone()) {
		_status = READED;
	} else {
		_status = READING;
	}
}


/*
** Checking request state
*/

void		Request::handleEndOfHeader() {
	size_t index = _buffer.find(END_OF_HEADER);

	if (index == std::string::npos) {
		return ;
	}

	_data.header = ParserRequest().parseHeader(_buffer.substr(0, index));
	// _buffer.erase(0, index + END_OF_HEADER.length());
	_buffer.erase(0, index);

	_isParsed = true;
}

bool		Request::isDone() {
	if (!_isParsed) //TODO очень важно написать правильные условия!!!
		return false;
	// if (_sup.method == "GET" || _sup.method == "DELETE") {
	// if (_buffer.find(END_OF_HEADER) == std::string::npos)
	// 	return false;
	// } else if (_sup.method == "POST") {
		
	// }
	_isParsed = false;
	return true;
}

void		Request::resetRequest() {
	_status = NO_REQUEST;
	// _buffer = "";
	_data.header.empty();
	_data.body.empty();
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