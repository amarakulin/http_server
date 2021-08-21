#include "utils.hpp"

void	toLowerCase(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void	printRequest(RequestData request) {
	std::cout << "<-- Header ->" << std::endl;
	for (requestHeaderStruct::iterator it = request.header.begin(); it != request.header.end(); it++) {
		std::cout << (*it).first << ": " << (*it).second << std::endl;
	}

	std::cout << "<-- Body ->" << std::endl;
	std::cout << request.body << std::endl;
}