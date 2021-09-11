#ifndef PARSER_CONFIG
# define PARSER_CONFIG

# include "Config.hpp"
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <cmath>
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
		Config*	parse(char* configFilePath);
		void	readConfigFile(char *configFilePath, std::list<std::string> *config);
		std::vector<HostData*>	devideConfigToComponents(std::list<std::string> config);
		bool	checkConfigString(std::string data);
		void	fillHostData(HostData *host, std::list<std::string>::iterator *it);
		void	checkHostData(HostData *host);
		void	enterDataToHostDataStruct(std::string const &key, std::string const &value, HostData *hostData);
		void	setDefaultHostValues(HostData *hostData);

		/*			SETTERS			*/

		void	setListenData(std::string data, HostData *hostData);
		void	setServerNameData(std::string data, HostData *hostData);
		void	setRootData(std::string data, HostData *hostData);
		void	setErrorPageData(std::string data, HostData *hostData);
		void	setClientMaxBodySizeData(std::string data, HostData *hostData);
		void	setLocationWayData(std::string data, HostData *hostData);
		void	setLocationDetailsData(std::string data, HostData *hostData);
		void	setRedirectToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setRootDataToLocation(std::string data, HostData *hostData, int	currentLocation);
		void	setMethodsToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setAutoindexToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setIndexToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setUploadEnableToLocation(std::string data, HostData *hostData, int	currentLocation);
		void	setUploadPathToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setCgiExtensionToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setCgiPathToLocation(std::string data, HostData *hostData, int currentLocation);
		void	setCgiRootToLocation(HostData *hostData, int currentLocation);

		class ParserConfigException : public std::exception {
			private:
				const char *msg;
			public:
				ParserConfigException(const std::string message) {
					msg = message.c_str();
				}
				
				virtual const char *what() const throw() {
					return msg;
				}
		};
};

#endif