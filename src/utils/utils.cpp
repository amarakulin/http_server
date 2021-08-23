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

bool	isLowerCase(std::string data) {
	for (int i = 0; i < data.length(); i++) {
		if (islower(data[i])) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}

std::vector<std::string>	split(std::string s, char delim) {
	std::vector<std::string> tmp;
	std::string buf = "";

	for (int i = 0; i < s.length(); i++) {
		if ((s[i] == ' ' || s[i] == ';') && buf.length() > 0) {
			tmp.push_back(buf);
			buf = "";
		} else {
			buf += s[i];
		}
	}
	return tmp;
}