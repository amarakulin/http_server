#include "utils.hpp"

void	toLowerCase(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void	toUpperCase(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
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

long	getSizeFile(const std::string &filename){
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

std::string			getDataFileAsString(const std::string &filename){
	std::stringstream buffer;
	std::ifstream file(filename);
	buffer << file.rdbuf();
	return buffer.str();
}

bool	isSomeSymbolInTheEnd(std::string end, char symbol) {
	if (end[end.length() - 1] == symbol && !end[end.length()]) {
		return true;
	} else {
		return false;
	}
}

bool	isFileInPath (const std::string& filePath){
	size_t posFile = filePath.find_last_of('/');
	return (filePath.find('.', posFile) != std::string::npos);
}

bool isFileExist (const std::string& filePath) {
	if (!isFileInPath(filePath)){
		return false;
	}
	struct stat buffer;
	return (stat (filePath.c_str(), &buffer) == 0);
}

bool isItemInVector(std::vector<std::string> vector, const std::string& val){
	for (size_t i = 0; i < vector.size(); ++i){
		if (vector[i] == val){
			return true;
		}
	}
	return false;
}
