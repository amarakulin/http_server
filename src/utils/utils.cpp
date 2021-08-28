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

long	getSizeFile(const std::string &filename){
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);
	//TODO test empty file, not exist file
	return rc == 0 ? stat_buf.st_size : -1;
}

std::string			getDataFileAsString(const std::string &filename){
	std::stringstream buffer;
	std::ifstream file(filename);
	//TODO test if not exist file
	buffer << file.rdbuf();
	return buffer.str();
}