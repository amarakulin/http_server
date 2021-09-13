#ifndef UTILS
# define UTILS

# include <vector>
# include <fstream>
# include <sstream>
# include <sys/stat.h>
#include "RequestTypes.hpp"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"                 /* Green */
#define SOME   "\033[37m"                 /* Green */
#define BLUE    "\033[34m"                 /* Blue */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

void	toLowerCase(std::string& str);
void	printRequest(RequestData request);
std::vector<std::string>	split(std::string value, std::string delim);
bool	hasLowerCaseLetter(std::string& str);
bool	hasUpperCaseLetter(std::string& str);
long			getSizeFile(const std::string &filename);
std::string		getDataFileAsString(const std::string &filename);
void	splitFirstArgiment(std::string s, std::string *key, std::string *value);
bool	isSomeSymbolInTheEnd(std::string end, char symbol);
bool	isFileExist (const std::string& filePath);
bool	isItemInVector(std::vector<std::string> vector, const std::string& val);

#endif