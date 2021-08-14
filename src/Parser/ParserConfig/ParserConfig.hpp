#ifndef PARSER_CONFIG
# define PARSER_CONFIG

class Config;

class ParserConfig {
	public:
		ParserConfig();
		Config& parse() const;
};

#endif