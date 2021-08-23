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
	void 						parse(char *configFilePath);
	std::list<std::string>		readConfigFile(char *configFilePath);
	void						devideConfigToComponents(std::list<std::string> config);
	bool						checkConfigString(std::string data);
	void						fillHostData(HostData *host, std::list<std::string>::iterator *it);
	void						checkHostData(HostData *host);
	void						ff();
	void						setListenData(std::string data, HostData *hostData);
	void						setServerNameData(std::string data, HostData *hostData);

	class ParserConfigException : public std::exception {
		public:
			virtual const char *what() const throw();
	};
};

#endif