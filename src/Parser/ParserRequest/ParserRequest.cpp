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
			// TODO bad request or ???request without body???
		}

	} else {
		return true;
	}
	return false;
}

bool		ParserRequest::handleEndOfBoundaryBody(RequestData& data, std::string& buffer) {
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

bool		ParserRequest::handleEndOfChunkedBody(RequestData& data, std::string& buffer) {
	if (data.header["transfer-encoding"] == "chunked") {
		data.body = parseBody(buffer);
		return true;
	}
	return false;
}

bool		ParserRequest::handleEndOfBodyWithContentLengt(RequestData& data, std::string& buffer) {
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

void		ParserRequest::parseCommonHeaderData(std::string& data, requestHeaderStruct& header) {
	std::string 				seporator = " ";
	std::vector<std::string>	tmp = split(data.substr(0, data.find("\r\n")), seporator);
	std::string 				str = data.substr(0, data.find(seporator));

	if (!hasUpperCaseLetter(*(tmp.end() - 1)))// Если протокол представлен в виде "http/1.1"
		joinUriPartOfCommonHeaderData(tmp.begin() + 1, tmp.end(), tmp);
	else
		joinUriPartOfCommonHeaderData(tmp.begin() + 1, tmp.end() - 1, tmp);

	if (tmp.size() == 2) // Если протокол представлен в виде "http/1.1", то подставляем дефолтное значение
		tmp.push_back("http/1.1");

	if (PROCESSED_REQUESTS.find(str) == std::string::npos) { // если не один из обрабатываемых методов не подходит
		if (!hasLowerCaseLetter(str)) {
			throw NotAllowedException();
		} else {
			throw BadRequestException();
		}
	}

	if (data.find(seporator) == 0 // если в начале строки стоит пробел
		|| (hasLowerCaseLetter(tmp[2]) && hasUpperCaseLetter(tmp[2]))) // если протокол представлен в виде "Http/1.1" | "HTTp/1.1"
		throw BadRequestException();


	for (int i = 0; COMMON_HEADE_DATA[i].length(); i++) {
		std::string value = tmp[i];
		if (COMMON_HEADE_DATA[i] != "uri")
			toLowerCase(value);
		header.insert(std::make_pair(COMMON_HEADE_DATA[i], value));
	}
	data.erase(0, data.find("\r\n", 0) + 2);
}

void	ParserRequest::joinUriPartOfCommonHeaderData(strVctIt start, strVctIt end, strVct& data) {
	std::vector<std::string> uriVct(start, end);
	std::string uri = ".";
	
	for (std::vector<std::string>::iterator it = uriVct.begin(); it != uriVct.end(); it++) {
		uri += (*it);
		if (it + 1 != uriVct.end())
			uri += " ";
	}
	data.erase(start, end);
	data.insert(start, uri);
}

void		ParserRequest::parseHeaderData(std::string& data, requestHeaderStruct& header) {
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

	parseCommonHeaderData(data, header);
	toLowerCase(data);
	parseHeaderData(data, header);

	if (header.find("host") == header.end())
		throw BadRequestException();

	return header;
}