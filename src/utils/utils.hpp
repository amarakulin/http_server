#ifndef UTILS
# define UTILS

# include <vector>
# include <fstream>
# include <sstream>
# include <sys/stat.h>
#include "RequestTypes.hpp"

void	toLowerCase(std::string& str);
void	printRequest(RequestData request);
std::vector<std::string>	split(std::string value, std::string delim);
bool	hasLowerCaseLetter(std::string& str);
bool	hasUpperCaseLetter(std::string& str);
long			getSizeFile(const std::string &filename);
std::string		getDataFileAsString(const std::string &filename);
void	splitFirstArgiment(std::string s, std::string *key, std::string *value);
std::vector<std::string>	split(std::string value, std::string delim);
bool	isSomeSymbolInTheEnd(std::string end, char symbol);

#endif