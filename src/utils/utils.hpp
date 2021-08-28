#ifndef UTILS
# define UTILS

# include <vector>
# include <iostream>
# include "RequestTypes.hpp"

void	toLowerCase(std::string& str);
void	printRequest(RequestData request);
void	splitFirstArgiment(std::string s, std::string *key, std::string *value);
std::vector<std::string>	split(std::string value, std::string delim);
bool	isSomeSymbolInTheEnd(std::string end, char symbol);

#endif