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
		handleEndOfHeader();
	if (_isHeaderParsed && !_isBodyParsed)
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
	_isHeaderParsed = true;
}

void		Request::handleEndOfBody() {
	std::string param;
	requestHeaderStruct::iterator end = _data.header.end();

	if (_data.header["method"] == "post") {

		if (_data.header.find("content-type") != end && _data.header.find("content-length") != end) {
			std::string contentType = _data.header["content-type"];

			if (contentType.find("boundary") != std::string::npos)
				handleEndOfBoundaryBody();
			else
				handleEndOfBodyWithContentLengt();

		} else if (_data.header.find("transfer-encoding") != end) {
			handleEndOfChunkedBody();
		}
		else {
			// TODO bad request
		}

	} else {
		_isBodyParsed = true;
	}
}

void	Request::handleEndOfBoundaryBody() {
	size_t		contentLength = std::stoi(_data.header["content-length"]);
	std::string contentType = _data.header["content-type"];

	std::string boundary = contentType.substr(contentType.find("=") + 1, contentType.length());
	if (boundary.find("\"") != std::string::npos) {
		boundary.erase(0, 1);
		boundary.pop_back();
	}

	if (_buffer.length() >= contentLength) {
		_data.body = ParserRequest::parseBody(_buffer, contentLength, boundary);
		_isBodyParsed = true;
	}
}

void	Request::handleEndOfChunkedBody() {
	if (_data.header["transfer-encoding"].find("chunked") != std::string::npos) {
		_data.body = ParserRequest::parseBody(_buffer);
		_isBodyParsed = true;
	}
}

void	Request::handleEndOfBodyWithContentLengt() {
	size_t		contentLength = std::stoi(_data.header["content-length"]);

	if (_buffer.length() >= contentLength) {
		_data.body = ParserRequest::parseBody(_buffer, contentLength);
		_isBodyParsed = true;
	}
}


/*
** Checking request state
*/

bool		Request::isDone() {
	if (!_isHeaderParsed || !_isBodyParsed)
		return false;
	printRequest(_data);
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