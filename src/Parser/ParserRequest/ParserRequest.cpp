#include "ParserRequest.hpp"

ParserRequest::ParserRequest() {}

ParserRequest::ParserRequest(const ParserRequest& other) {
	*this = other;
}

ParserRequest::~ParserRequest() {}

/*
** Parse body
*/

// void	ParserRequest::parseBodyWithContentLength(std::string& data, std::string& body) {
// 	body = data;
// }

// void	ParserRequest::parseBodyBoundary(std::string& data, int contentLengt) {

// }

// void	ParserRequest::parseBodyChunked(std::string& data, std::string& body) {

// }

std::string			ParserRequest::parseBody(std::string& data) {
	std::string body;
	return body;
}

std::string			ParserRequest::parseBody(std::string& data, int contentLengt) {
	std::string body;

	body = data.substr(0, contentLengt);
	data.erase(0, contentLengt);
	std::cout << "/* message */" << std::endl;

	return body;
}

std::string			ParserRequest::parseBody(std::string& data, int contentLengt, std::string boundary) {
	std::string body;
	std::string firstKeySeporator = "name=\"";
	std::string secondKeySeporator = "\"";

	size_t		start = 0;
	size_t		end = 0;

	std::cout << "Body: " << std::endl << data << std::endl;
	// std::cout << "Boundary:" << std::endl << boundary << std::endl;
	size_t boundaryCount = 0;

	do  {
		start = data.find(boundary, start) + boundary.length();
		// std::cout << data.c_str() + start << std::endl;
		boundaryCount++;
	} while ((*(data.c_str() + start) != '-' && *(data.c_str() + start + 1) != '-'));

	start = 0;
	std::cout << "count" << boundaryCount << std::endl;

	for (int i = 0; i < boundaryCount - 1; i++) {

		start = data.find(firstKeySeporator, end) + firstKeySeporator.length();
		end = data.find(secondKeySeporator, start);

		// std::cout << "Start: " << start << std::endl;
		// std::cout << "End: " << end << std::endl;

		body += data.substr(start, end - start) + "=";
		// std::cout << "Key: |" << body << "|" << std::endl;

		start = data.find(END_OF_HEADER, end) + END_OF_HEADER.length();
		end = data.find("\r\n", start);

		if (end == std::string::npos) {
			std::cout << "/* message */" << std::endl;
			// break ;
		}

		body += data.substr(start, end - start) + " ";


		// std::cout << "Start: " << data[start] << std::endl;
		// std::cout << "End: " << data[end - 1] << std::endl;


		// std::cout << "Value: " << data.substr(start, end - start) << std::endl;
	}

		std::cout << "-<<<" << body << std::endl;

	data.erase(0, contentLengt);
	return body;
}

/*
** Parse header
*/

void	ParserRequest::parseCommonHeaderData(std::string& data, requestHeaderStruct& header) {
	size_t 		index;
	std::string seporator = " ";

	for (int i = 0; COMMON_HEADE_DATA[i].length(); i++) {
		if (COMMON_HEADE_DATA[i] == "protocol")
			seporator = "\n";
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