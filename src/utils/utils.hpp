#ifndef UTILS
# define UTILS

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <sys/stat.h>

//FOR Debug for lovely Clion
#include "../Types/RequestTypes.hpp"

void	toLowerCase(std::string& str);
void	printRequest(RequestData request);
long			getSizeFile(const std::string &filename);
std::string		getDataFileAsString(const std::string &filename);

#endif