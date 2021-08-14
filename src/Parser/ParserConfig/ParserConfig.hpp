#ifndef PARSER_CONFIG
# define PARSER_CONFIG

# include "Config.hpp"

class Config;

class ParserConfig {
	public:
		ParserConfig();
		Config* parse(char** configFilePath) const;
};

#endif