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

std::vector<std::string>	split(std::string value, std::string delim) {
	std::vector<std::string> tmp;
	size_t start = 0;
	size_t end = 0;

	while (start != value.length() && end != std::string::npos) {
		end = value.find(delim, start);

		if (end == std::string::npos) {
				tmp.push_back(value.substr(start, end - start));
		} else {
			if (start - end != 0)
				tmp.push_back(value.substr(start, end - start));
			start = end + delim.length();
		}
	}
	return tmp;
}

bool	hasLowerCaseLetter(std::string& str) {
	size_t len = str.length();
	for (size_t i = 0; i < len; i++) {
		if (islower(str[i]))
			return true;
	}
	return false;
}

bool	hasUpperCaseLetter(std::string& str) {
	size_t len = str.length();
	for (size_t i = 0; i < len; i++) {
		if (isupper(str[i]))
			return true;
	}
	return false;
}