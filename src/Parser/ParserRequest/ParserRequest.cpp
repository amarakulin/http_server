#include "ParserRequest.hpp"

ParserRequest::ParserRequest() {}

ParserRequest::ParserRequest(const ParserRequest& other) {}

ParserRequest::~ParserRequest() {}

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


	for (requestHeaderStruct::iterator it = header.begin(); it != header.end(); it++)
		std::cout << (*it).first << ": " << (*it).second << std::endl;
}


requestHeaderStruct ParserRequest::parseHeader(std::string data) {
	requestHeaderStruct header;
	toLowerCase(data);

	parseCommonHeaderData(data, header);
	parseHeaderData(data, header);

	return header;
}