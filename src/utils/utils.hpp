#ifndef UTILS
# define UTILS

# include <vector>
# include <fstream>
# include <sstream>
# include <sys/stat.h>
#include "RequestTypes.hpp"
#include "algorithm"
#include "dirent.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"                 /* Green */
#define SOME   "\033[37m"                 /* Green */
#define BLUE    "\033[34m"                 /* Blue */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

#define FILENAME_SEPORATOR "==filename=="

void	toLowerCase(std::string& str);
void	toUpperCase(std::string& str);
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
std::vector<std::string> listOfFiles(const std::string& pattern);

// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
	my_equal( const std::locale& loc ) : loc_(loc) {}
	bool operator()(charT ch1, charT ch2) {
		return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
	}
private:
	const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
{
	typename T::const_iterator it = std::search( str1.begin(), str1.end(),
												 str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
	if ( it != str1.end() ) return it - str1.begin();
	else return -1; // not found
}

#endif