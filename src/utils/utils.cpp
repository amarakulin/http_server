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

std::vector<std::string>	split(std::string value, std::string delim) {
	std::vector<std::string> tmp;
	size_t start = 0;
	size_t end = 0;

	while (end <= value.length()) {
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

bool	isSomeSymbolInTheEnd(std::string end, char symbol) {
	if (end[end.length() - 1] == symbol && !end[end.length()]) {
		return true;
	} else {
		return false;
	}
}