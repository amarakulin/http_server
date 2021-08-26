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

void	splitFirstArgiment(std::string s, std::string *key, std::string *value) {
	const int delim = s.find_first_of(' ');

	*key = s.substr(0, delim);
	*value = s.substr(delim + 1, s.length());
}

std::vector<std::string>	split(std::string value) {
	std::vector<std::string> tmp;
	std::string buf;

	for (int i = 0; i < value.length(); i++) {
		if (value[i] == ' ' || value[i] == ';') {
			tmp.push_back(buf);
			buf = "";
		} else {
			buf += value[i];
		}
	}
	return tmp;
}

bool	isSomeSymbolInTheEnd(std::string end, char symbol) {
	if (end[end.length() - 1] == symbol && !end[end.length()]) {
		return true;
	} else {
		return false;
	}
}