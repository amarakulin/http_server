#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

// Config* ParserConfig::parse(char* configFilePath) {
void ParserConfig::parse(char *configFilePath) {
	// Config *config = new Config();
	std::list<std::string> config;
	try {
		config = readConfigFile(configFilePath);
		devideConfigToComponents(config);
	} catch (ParserConfigException e) {
		std::cout << e.what() << std::endl;
	}

	// config->setNewHost(Host("127.0.0.1", 8000, "localhost"));
	// co fig->setNewHost(Host("400.2.3.1", 5050, "my-site.com"));
	// return config;
}

std::list<std::string> ParserConfig::readConfigFile(char *configFilePath) {
	std::ifstream input;
	std::string buf;
	std::list<std::string> config;

	input.open(configFilePath);
	if (!input.is_open()) {
		std::cout << "File open error" << std::endl;
	}
	while (std::getline(input, buf)) {
		config.push_back(buf);
	}
	input.close();
	return config;
}

void	ParserConfig::ff() {
	std::map<std::string, std::string> map;
	HostData	hostData;


	// map.insert(std::make_pair("listen", "127.0.0.1:8000;"));
	map.insert(std::make_pair("server_name", "localhost;"));
	std::map<std::string, std::string>::iterator end = map.end();
	std::map<std::string, std::string>::iterator cur;

	for (int i = 0; i < SIZE_OF_KEYS; i++) {
		cur = map.find(keys[i]);
		if (cur != end) {
			std::string key = (*cur).first;
			std::string value = (*cur).second;
			if (key == "listen") {
				// TODO validation
				setListenData(value, &hostData);
			} else if (key == "server_name") {
				// TODO validation
				setServerNameData(value, &hostData);
			} else if (key == "root") {
				// TODO
				setRootData(value, &hostData);
			} else if (key == "error_page") {
				// TODO
				setErrorPageData(value, &hostData);
			} else if (key == "client_max_body_size") {
				// TODO
				setClientMaxBodySizeData(value, &hostData);
			} else if (key == "location") {
				// TODO: send iterator,structure and value(the way)
				setLocationData();
			}
		}
	}
}

void	ParserConfig::setServerNameData(std::string data, HostData *hostData) {
	std::cout << data << std::endl;
}

/*
*	Set host and port data to HostData structure
* 	TODO: Validation
*/

void	ParserConfig::setListenData(std::string data, HostData *hostData) {
	const int delim = data.find_first_of(':');
	const char *port;
	char *remainder;

	if (!(delim > 0 && delim < data.size())) {
		std::cout << "error!!!" << std::endl;
	}

	hostData->host = data.substr(0, delim);
	port = data.substr(delim + 1, data.length()).c_str();
	hostData->port = std::strtol(port, &remainder, 0);

	if (remainder[0] == ';' && !remainder[1]) {

	} else {
		std::cout << "error!!!" << std::endl;
	}
}

void	ParserConfig::devideConfigToComponents(std::list<std::string> config) {
	HostData data;
	std::list<std::string>::iterator it = config.begin();

	ff();
	// for (; it != config.end(); it++) {
	// 	if ((*it) == "***") {
	// 		checkHostData(&data);
	// 	} else {
	// 		if (checkConfigString(*it)) {
	// 			fillHostData(&data, &it);
	// 		} else {
	// 			// throw ParserConfigException();
	// 		}
	// 	}
	// }
}

const char *ParserConfig::ParserConfigException::what() const throw() {
	return "Parcer error";
}


/*
** Проверяет строку на ключевые слова
*/

bool	ParserConfig::checkConfigString(std::string data) {
	std::vector<std::string> tmp = split(data, ' ');
	// if ()
	std::cout << "_____" << std::endl;
	for (int i = 0; i < tmp.size(); i++) {
		std::cout << tmp[i] << std::endl;
	}
	return true;
}

void	ParserConfig::fillHostData(HostData *host, std::list<std::string>::iterator *it) {

}

/*
* Проверяет все поля HostData прежду, чем создавать новый хост.
* Если невалидно, выбрасывает исключение.
*/

void	ParserConfig::checkHostData(HostData *host) {

}
