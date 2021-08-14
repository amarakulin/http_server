#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

Config* ParserConfig::parse(char* configFilePath) const {
	Config *config = new Config();
	std::cout << configFilePath << std::endl;

	config->setNewHost(Host("127.0.0.1", 8000, "localhost"));
	config->setNewHost(Host("400.2.3.1", 5050, "my-site.com"));
	return config;
}