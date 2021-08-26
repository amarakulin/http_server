#ifndef PARSER_CONFIG
# define PARSER_CONFIG

// # include "Config.hpp"
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <climits>
# include "HostTypes.hpp"
# include "utils.hpp"

class Config;

/*
** Класс читает данные из конфигурационного файла и парсит их
*/

class ParserConfig {
public:
	ParserConfig();
	// Config*					parse(char* configFilePath);
	void 	parse(char *configFilePath);
	void	readConfigFile(char *configFilePath, std::list<std::string> *config);
	void	devideConfigToComponents(std::list<std::string> config, HostData *hostData);
	bool	checkConfigString(std::string data);
	void	fillHostData(HostData *host, std::list<std::string>::iterator *it);
	void	checkHostData(HostData *host);
	void	enterDataToHostDataStruct(std::string const &key, std::string const &value, HostData *hostData);

	/*			SETTERS			*/

	void	setListenData(std::string data, HostData *hostData);
	void	setServerNameData(std::string data, HostData *hostData);
	void	setRootData(std::string data, HostData *hostData);
	void	setErrorPageData(std::string data, HostData *hostData);
	void	setClientMaxBodySizeData(std::string data, HostData *hostData);
	void	setLocationWayData(std::string data, HostData *hostData);
	void	setLocationDetailsData(std::string data, HostData *hostData);
	void	setRootDataToLocation(std::string data, HostData *hostData, int	currentLocation);
	void	setMethodsToLocation(std::string data, HostData *hostData, int currentLocation);
	void	setAutoindexToLocation(std::string data, HostData *hostData, int currentLocation);
	void	setIndexToLocation(std::string data, HostData *hostData, int currentLocation);
	void	setUploadEnableToLocation(std::string data, HostData *hostData, int	currentLocation);
	void	setUploadPathToLocation(std::string data, HostData *hostData, int currentLocation);
	void	setCgiExtencionToLocation(std::string data, HostData *hostData, int	currentLocation);
	void	setCgiPathToLocation(std::string data, HostData *hostData, int currentLocation);

	class ParserConfigException : public std::exception {
		public:
			virtual const char *what() const throw();
	};
};

#endif