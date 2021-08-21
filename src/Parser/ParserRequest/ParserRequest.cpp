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


requestHeaderStruct ParserRequest::parseHeader(std::string data) {
	requestHeaderStruct header;
	toLowerCase(data);

	parseCommonHeaderData(data, header);

	// std::cout << "Data: " << std::endl << data << std::endl;

	// // data.find(SPLIT_STRING);
	

	// std::cout << "---> " << std::endl << header["method"] << std::endl;

	return header;
}