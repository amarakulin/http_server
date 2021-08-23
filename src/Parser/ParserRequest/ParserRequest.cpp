#include "ParserRequest.hpp"

ParserRequest::ParserRequest() {}

ParserRequest::ParserRequest(const ParserRequest &other) {
	*this = other;
}

ParserRequest::~ParserRequest() {}

/*
** Handling request parts
*/

bool		ParserRequest::handleEndOfHeader(requestHeaderStruct& header, std::string& buffer) {
	size_t index = buffer.find(END_OF_HEADER);

	if (index == std::string::npos) {
		return false;
	}

	header = parseHeader(buffer.substr(0, index));
	buffer.erase(0, index + END_OF_HEADER.length());
	return true;
}

bool		ParserRequest::handleEndOfBody(RequestData& data, std::string& buffer) {
	// std::cout << "Buffer: " << buffer << std::endl;
	
	requestHeaderStruct::iterator end = data.header.end();

	if (REQUEST_WITH_BODY.find(data.header["method"]) != std::string::npos) {
		bool hasContetnType = data.header.find("content-type") != end;
		bool hasContentLength = data.header.find("content-length") != end;

		if (hasContetnType && hasContentLength) {
			std::string contentType = data.header["content-type"];

			if (contentType.find("boundary") != std::string::npos)
				return handleEndOfBoundaryBody(data, buffer);
			else
				return handleEndOfBodyWithContentLengt(data, buffer);

		} else if (hasContentLength) {
			return handleEndOfBodyWithContentLengt(data, buffer);
		}  else if (data.header.find("transfer-encoding") != end) {
			return handleEndOfChunkedBody(data, buffer);
		}
		else {
			// TODO bad request
		}

	} else {
		return true;
	}
	return false;
}

bool	ParserRequest::handleEndOfBoundaryBody(RequestData& data, std::string& buffer) {
	size_t		contentLength = std::stoi(data.header["content-length"]);
	std::string contentType = data.header["content-type"];

	std::string boundary = contentType.substr(contentType.find("=") + 1, contentType.length());
	if (boundary.find("\"") != std::string::npos) {
		boundary.erase(0, 1);
		boundary.pop_back();
	}

	if (buffer.length() >= contentLength) {
		data.body = parseBody(buffer, contentLength, boundary);
		return true;
	}
	return false;
}

bool	ParserRequest::handleEndOfChunkedBody(RequestData& data, std::string& buffer) {
	if (data.header["transfer-encoding"] == "chunked") {
		data.body = parseBody(buffer);
		return true;
	}
	return false;
}

bool	ParserRequest::handleEndOfBodyWithContentLengt(RequestData& data, std::string& buffer) {
	size_t		contentLength = std::stoi(data.header["content-length"]);

	if (buffer.length() >= contentLength) {
		data.body = parseBody(buffer, contentLength);
		return true;
	}
	return false;
}

/*
** Parse body
*/

std::string ParserRequest::parseBody(std::string &data) {
	std::string body;
	std::string chunk;

	size_t pos = 0;
	size_t len = 0;

	while (data != END_OF_CHUNKED_BODY) {
		len = std::stoi(data, 0, 16);
		pos = data.find("\r\n") + 2;

		chunk = data.substr(pos, len);

		if (!chunk.length())
			break ;

		body += chunk + " ";

		data.erase(0, data.substr(0, pos + 2).length() + len); //TODO Оптимизировать
	}
	data.erase(0, END_OF_CHUNKED_BODY.length());

	return body;
}

std::string ParserRequest::parseBody(std::string &data, int contentLengt) {
	std::string body;

	body = data.substr(0, contentLengt);
	data.erase(0, contentLengt);

	return body;
}

std::string ParserRequest::parseBody(std::string &data, int contentLengt, std::string boundary) {
	std::string body;
	std::string firstKeySeporator = "filename=\"";
	std::string secondKeySeporator = "\"";

	size_t start = 0;
	size_t end = 0;

	std::string chunk;
	size_t pos = 0;

	while ((pos = data.find(boundary)) != std::string::npos) {
		chunk = data.substr(0, pos);

		if ((start = chunk.find(firstKeySeporator, end)) != std::string::npos)
			body += parseBoundaryChunk(chunk);

		data.erase(0, pos + boundary.length());
	}
	data.erase(0, END_OF_HEADER.length() + 2);
	return body;
}

std::string ParserRequest::parseBoundaryChunk(std::string& chunk) {
	std::string parsedData;
	std::string firstKeySeporator = "filename=\"";
	std::string secondKeySeporator = "\"";

	size_t start = 0;
	size_t end = 0;

	start = chunk.find(firstKeySeporator, end) + firstKeySeporator.length();
	end = chunk.find(secondKeySeporator, start);
	parsedData += chunk.substr(start, end - start) + "=";

	start = chunk.find(END_OF_HEADER, end) + END_OF_HEADER.length();
	end = chunk.find("\r\n", start);
	parsedData += chunk.substr(start, end - start) + " ";

	return parsedData;
}

/*
** Parse header
*/

void	ParserRequest::parseCommonHeaderData(std::string& data, requestHeaderStruct& header) {
	size_t 		index;
	std::string seporator = " ";

	for (int i = 0; COMMON_HEADE_DATA[i].length(); i++) {
		if (COMMON_HEADE_DATA[i] == "protocol")
			seporator = "\r\n";
		index = data.find(seporator);
		header.insert(std::make_pair(COMMON_HEADE_DATA[i], data.substr(0, index)));
		data.erase(0, index + seporator.length());
	}
}

void	ParserRequest::parseHeaderData(std::string& data, requestHeaderStruct& header) {
	std::pair<std::string, std::string> headerParam;
	size_t start = 0;
	size_t end = 0;

	while (true) {
		start = data.find(SEPORATOR, end);
		if (start == std::string::npos)
			start = data.rfind(SEPORATOR, data.length());
		headerParam.first = data.substr(end, start > end ? start - end : end - start);
		start += SEPORATOR.length();

		end = data.find(END_OF_LINE, start);
		if (end == std::string::npos) {
			end = data.length();
			headerParam.second = data.substr(start, end - start);
			header.insert(headerParam);
			break ;
		}
		headerParam.second = data.substr(start, end - start);
		end += END_OF_LINE.length();

		header.insert(headerParam);
	}
}

requestHeaderStruct ParserRequest::parseHeader(std::string data) {
	requestHeaderStruct header;
	toLowerCase(data);

	parseCommonHeaderData(data, header);
	parseHeaderData(data, header);

	return header;
}