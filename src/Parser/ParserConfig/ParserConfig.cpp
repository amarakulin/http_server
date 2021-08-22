#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

// Config* ParserConfig::parse(char* configFilePath) {
void ParserConfig::parse(char *configFilePath)
{
	// Config *config = new Config();
	std::list<std::string> config;
	try
	{
		config = readConfigFile(configFilePath);

	}
	catch (ParserConfigException e)
	{
		std::cout << e.what() << std::endl;
	}

	// config->setNewHost(Host("127.0.0.1", 8000, "localhost"));
	// co fig->setNewHost(Host("400.2.3.1", 5050, "my-site.com"));
	// return config;
}

std::list<std::string> ParserConfig::readConfigFile(char *configFilePath)
{
	std::ifstream input;
	std::string buf;
	std::list<std::string> config;

	input.open(configFilePath);
	if (!input.is_open())
	{
		std::cout << "File open error" << std::endl;
	}
	while (std::getline(input, buf))
	{
		config.push_back(buf);
		std::cout << buf << std::endl;
	}
	input.close();
	return config;
}

void	devideConfigToComponents() {
	
}

const char *ParserConfig::ParserConfigException::what() const throw() {
	return "Parcer error";
}