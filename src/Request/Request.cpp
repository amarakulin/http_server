#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _buffer(), _isHeaderParsed(false), _isBodyParsed(false) {}

Request::Request(const Request& other)
	: _status(other._status), _buffer(other._buffer),
	_isHeaderParsed(other._isHeaderParsed), _isBodyParsed(other._isBodyParsed) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_buffer += chunk;

	if (!_isHeaderParsed)
		_isHeaderParsed = ParserRequest::handleEndOfHeader(_data.header, _buffer);
	if (_isHeaderParsed && !_isBodyParsed)
		_isBodyParsed = ParserRequest::handleEndOfBody(_data, _buffer);

	if (isDone()) {
		_status = READED;
	} else {
		_status = READING;
	}
}

/*
** Checking request state
*/

bool		Request::isDone() {
	if (!_isHeaderParsed || !_isBodyParsed)
		return false;
	// printRequest(_data);
	return true;
}

void		Request::resetRequest() {
	_status = NO_REQUEST;
	_isHeaderParsed = false;
	_isBodyParsed = false;
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

void Request::setData(const RequestData &data){
	_data = data;
}
