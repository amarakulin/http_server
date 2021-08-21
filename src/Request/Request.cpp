#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _buffer() {}

Request::Request(const Request& other)
	: _status(other._status), _buffer(other._buffer) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_buffer += chunk;

	handleEndOfHeader();
	handleEndOfBody();
	
	if (isDone()) {
		_status = READED;
	} else {
		_status = READING;
	}
}


/*
** Handling request parts
*/

void		Request::handleEndOfHeader() {
	size_t index = _buffer.find(END_OF_HEADER);

	if (index == std::string::npos) {
		return ;
	}

	_data.header = ParserRequest::parseHeader(_buffer.substr(0, index));
	_buffer.erase(0, index + END_OF_HEADER.length());
	_isParsed = true;
}

void		Request::handleEndOfBody() {
	std::string method = _data.header["method"];
	

	// if (method == "post") {
	// 	try {
	// 		size_t len = std::stoi(_data.header["content-length"]);
	// 		_data.body = ParserRequest::parseBody(_buffer, WITH_CONTENT_LEN);
	// 	} catch (std::exception e) {
	// 		std::cout << "Error: " << e.what() << std::endl;
	// 	}
	// }


	// std::cout << "Content-length: " << contenLength << std::endl;

}

/*
** Checking request state
*/

bool		Request::isDone() {
	if (!_isParsed)
		return false;
	_isParsed = false;
	return true;
}

void		Request::resetRequest() {
	_status = NO_REQUEST;
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