#include "Request.hpp"

Request::Request()
	: _status(NO_REQUEST), _buffer(), _isHeaderParsed(false), _isBodyParsed(false) {}

Request::Request(const Request& other)
	: _status(other._status), _buffer(other._buffer),
	_isHeaderParsed(other._isHeaderParsed), _isBodyParsed(other._isBodyParsed) {}

Request::~Request() {}

void		Request::addRequestChunk(std::string chunk) {
	_buffer += chunk;

	// std::cout << "Before parsing header: " << _buffer << std::endl;
	if (!_isHeaderParsed)
		handleEndOfHeader();
	else if (_isHeaderParsed && !_isBodyParsed)
		handleEndOfBody();
	// std::cout << "Before parsing body: " << _buffer << std::endl;


	// std::cout << "Buffer: " << _buffer << std::endl;
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
	_isHeaderParsed = true;
}

void		Request::handleEndOfBody() {
	std::string param;
	requestHeaderStruct::iterator end = _data.header.end();

	if (_data.header["method"] == "post") {

		if (_data.header.find("content-type") != end && _data.header.find("content-length") != end) {

			size_t contentLength = std::stoi(_data.header["content-length"]);

			if (_data.header["content-type"].find("boundary") != std::string::npos) {
				std::cout << "<--- Boundary --->" << std::endl;

				std::string contentType = _data.header["content-type"];
				std::string boundary = contentType.substr(contentType.find("=") + 1, contentType.length());

				if (_buffer.length() >= contentLength) {
					_data.body = ParserRequest::parseBody(_buffer, contentLength, boundary);
					_isBodyParsed = true;
				}

			} else {
				std::cout << "<--- Content length --->" << std::endl;

				if (_buffer.length() >= contentLength) {
					_data.body = ParserRequest::parseBody(_buffer, contentLength);
					_isBodyParsed = true;
				}
			}
		} 
		// // else if (_data.header.find("transfer-encoding") != end) {
		// // 	if (_data.header["transfer-encoding"].find("chunked") != std::string::npos)
		// // 		_data.body = ParserRequest::parseBody(_buffer, CHUNKED);
		// // }
		// else {
		// 	// TODO bad request
		// }

	} else {
		_isBodyParsed = true;
	}

	// _isParsed = true;
}

/*
** Checking request state
*/

bool		Request::isDone() {
	if (!_isHeaderParsed || !_isBodyParsed)
		return false;
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