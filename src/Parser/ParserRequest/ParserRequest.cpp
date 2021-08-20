#include "ParserRequest.hpp"

ParserRequest::ParserRequest() {}

ParserRequest::ParserRequest(const ParserRequest& other) {}

ParserRequest::~ParserRequest() {}

/*
** Parse header
*/

// void	parseMethod(std::string& data, requestHeaderStruct& header) {
// 	size_t index = data.find(" ");

// 	header.insert(std::make_pair("method", data.substr(0, index)));
// 	data.erase(0, index);
// }

// void	parseLocation(std::string& data, requestHeaderStruct& header) {
	
// }

// void	parseProtocol(std::string& data, requestHeaderStruct& header) {
	
// }


requestHeaderStruct ParserRequest::parseHeader(std::string data) {
	requestHeaderStruct header;
	// toLowerCase(data);

	// parseMethod(data, header);

	// std::cout << "Data: " << std::endl << data << std::endl;

	// // data.find(SPLIT_STRING);
	

	// std::cout << "---> " << std::endl << header["method"] << std::endl;

	return header;
}