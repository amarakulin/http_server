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
	size_t 		index;
	size_t 		endOfLineIndex;
	std::string seporator = ": ";
	std::pair<std::string, std::string> headerNode;

	size_t start = 0;
	size_t end = 0;

	do {
		start = data.find(seporator, end);
		headerNode.first = data.substr(end, start);

		std::cout << "First: |" << headerNode.first << "|" << std::endl;


		end = data.find("\r\n", start);
		if (end == std::string::npos)
			end = data.length();
		headerNode.second = data.substr(start + seporator.length(), end);

		// std::cout << "|" << headerNode.first << ": " << headerNode.second << "|" << std::endl;

		header.insert(headerNode);
	} while (start != std::string::npos);

	// headerNode.first = data.substr(0, index);
	// headerNode.second = data.substr(index + seporator.length(), endOfLineIndex);
	// header.insert(headerNode);

	// while (data.length()) {
	// 	index = data.find(seporator);
	// 	endOfLineIndex = data.find("\n");
	// 	if (endOfLineIndex == std::string::npos)
	// 		endOfLineIndex = data.length();

	// 	headerNode.first = data.substr(0, index);
	// 	headerNode.second = data.substr(index + seporator.length(), endOfLineIndex);

	// 	// header.insert(std::make_pair(data.substr(0, index), data.substr(index + seporator.length(), endOfLineIndex)));
	// 	// data.erase(0, endOfLineIndex + 1);
	// }

	std::cout << "<---- Size ----> " << header.size() << std::endl;

	// for (requestHeaderStruct::iterator it = header.begin(); it != header.end(); it++) {
	// 	std::cout << (*it).first << ": " << (*it).second << std::endl;
	// }
}


requestHeaderStruct ParserRequest::parseHeader(std::string data) {
	requestHeaderStruct header;
	toLowerCase(data);

	std::cout << "Data: " << std::endl << data << std::endl << std::endl;

	parseCommonHeaderData(data, header);
	parseHeaderData(data, header);

	// std::cout << "Data: " << std::endl << data << std::endl;

	// // data.find(SPLIT_STRING);
	

	// std::cout << "---> " << std::endl << header["method"] << std::endl;

	return header;
}