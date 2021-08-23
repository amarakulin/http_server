#ifndef UTILS
# define UTILS

# include <vector>
# include <iostream>
# include "RequestTypes.hpp"

void	toLowerCase(std::string& str);
void	printRequest(RequestData request);
std::vector<std::string>	split(std::string s, char delim);

#endif