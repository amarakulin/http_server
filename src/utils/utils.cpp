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
	if (end[end.length() - 1] == symbol && end[end.length() - 2] != symbol && !end[end.length()]) {
		return true;
	} else {
		return false;
	}
}

bool isFileExist (const std::string& filePath) {
	DIR *dir;
	struct dirent *ent;
	size_t posSeparator = filePath.find_last_of('/');
	std::string filename;
	std::string path;

	if (posSeparator == std::string::npos){
		return false;
	}
	filename = filePath.substr(posSeparator + 1, filePath.size() - posSeparator + 1);
	path = filePath.substr(0, posSeparator);
	if ((dir = opendir (path.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (ent->d_type == 8 && filename == ent->d_name){// 8 is type of a file
				closedir (dir);
				return true;
			}
		}
		closedir (dir);
	} else {
//		std::cout << "Error to serch in dir: " << path << std::endl;
	}
//	if (!isFileInPath(filePath)){
//		return false;
//	}
//	struct stat buffer;
//	return (stat (filePath.c_str(), &buffer) == 0);
	return false;
}

bool isItemInVector(std::vector<std::string> vector, const std::string& val){
	for (size_t i = 0; i < vector.size(); ++i){
		if (vector[i] == val){
			return true;
		}
	}
	return false;
}

std::vector<std::string> listOfFiles(const std::string& pattern){
	std::vector<std::string> listDir;
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir (pattern.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (ent->d_type == 8){// 8 is type of a file
				listDir.push_back(ent->d_name);
			}
		}
		closedir (dir);
	}
	return listDir;
}

std::string gen_random(const int len) {

	std::string tmp_s;
	static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

	srand( (unsigned) time(NULL) * getpid());

	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i)
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


	return tmp_s;

}