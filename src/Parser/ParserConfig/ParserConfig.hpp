#ifndef PARSER_CONFIG
# define PARSER_CONFIG

// # include "Config.hpp"
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <climits>

class Config;

class ParserConfig
{
private:
	std::map<std::string, std::string> params;
	std::map<std::string, std::string> locations;

public:
	ParserConfig();
	// Config*					parse(char* configFilePath);
	void 					parse(char *configFilePath);
	std::list<std::string>	readConfigFile(char *configFilePath);
	void					devideConfigToComponents();

	class ParserConfigException : public std::exception {
		public:
			virtual const char *what() const throw();
	};
};

#endif