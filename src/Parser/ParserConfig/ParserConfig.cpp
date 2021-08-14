#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

Config* ParserConfig::parse(char* configFilePath) const {
	Config *config = new Config();
	std::cout << configFilePath << std::endl;
	return config;
}