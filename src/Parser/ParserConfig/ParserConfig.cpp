#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

Config* ParserConfig::parse(char** configFilePath) const {
	Config *config = new Config();
	configFilePath += 1; //! DELETE ONLY FOR COMPILE
	return config;
}