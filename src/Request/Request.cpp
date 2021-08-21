#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _buffer() {}

Request::Request(const Request& other)
	: _status(other._status), _buffer(other._buffer) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_buffer += chunk;

	// std::cout << "Before parsing header: " << _buffer << std::endl;
	handleEndOfHeader();
	// std::cout << "Before parsing body: " << _buffer << std::endl;
	handleEndOfBody();

	// std::cout << "Body: " << _data.body << std::endl;
	// std::cout << "After parsing: " << _buffer << std::endl;
	
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
	if (_data.header["method"] != "post")
		_isParsed = true;
}

void		Request::handleEndOfBody() {
	std::string param;
	requestHeaderStruct::iterator end = _data.header.end();
	
	if ( _data.header["method"] == "post") {

		if (_data.header.find("content-length") != end) {
			std::string sub = _buffer.substr(0, std::stoi(_data.header["content-length"]));

			_data.body = ParserRequest::parseBody(sub, WITH_CONTENT_LEN);
			_buffer.erase(0, sub.length());
		} else if (_data.header.find("content-type") != end) {
			if (_data.header["content-type"].find("boundary") != std::string::npos)
				_data.body = ParserRequest::parseBody(_buffer, BOUNDARY);
		} else if (_data.header.find("transfer-encoding") != end) {
			if (_data.header["transfer-encoding"].find("chunked") != std::string::npos)
				_data.body = ParserRequest::parseBody(_buffer, CHUNKED);
		}

	}

	_isParsed = true;
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
	_data.header.clear();
	_data.body.clear();
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