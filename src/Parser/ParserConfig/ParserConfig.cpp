#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

// Config* ParserConfig::parse(char* configFilePath) {
void	ParserConfig::parse(char *configFilePath) {
	HostData hostData;
	// Config *config = new Config();
	std::list<std::string> config;
	try {
		readConfigFile(configFilePath, &config);
		devideConfigToComponents(config, &hostData);
		// std::cout << hostData.host << std::endl;
		// std::cout << hostData.port << std::endl;
		// std::cout << hostData.serverName << std::endl;
		// std::cout << hostData.root << std::endl;
		// std::cout << hostData.errorPage.errorNumber << std::endl;
		// std::cout << hostData.errorPage.locationOfErrorPage << std::endl;
		// std::cout << hostData.clientMaxBodySize << std::endl;
		// std::cout << hostData.location[hostData.location.size()].way << std::endl;
		// std::cout << hostData.location[hostData.location.size()].root << std::endl;
		// std::cout << hostData.location[hostData.location.size()].httpMethods[0] << std::endl;
	} catch (ParserConfigException e) {
		std::cout << e.what() << std::endl;
	}

	// config->setNewHost(Host("127.0.0.1", 8000, "localhost"));
	// config->setNewHost(Host("400.2.3.1", 5050, "my-site.com"));
	// return config;
}

/*
**	Reading config file to list
*/

void	ParserConfig::readConfigFile(char *configFilePath, std::list<std::string> *config) {
	std::ifstream input;
	std::string buf;

	input.open(configFilePath);
	if (!input.is_open()) {
		std::cout << "File open error" << std::endl;
	}
	while (std::getline(input, buf)) {
		(*config).push_back(buf);
	}
	input.close();
}

/*
**	Check and enter data to HostData structure
*/

void	ParserConfig::enterDataToHostDataStruct(std::string const &key, std::string const &value, HostData *hostData) {
	if (key == "listen") {
		// TODO validation
		setListenData(value, hostData);
	} else if (key == "server_name") {
		// TODO validation
		setServerNameData(value, hostData);
	} else if (key == "root") {
		// TODO
		setRootData(value, hostData);
	} else if (key == "error_page") {
		// TODO
		setErrorPageData(value, hostData);
	} else if (key == "client_max_body_size") {
		// TODO
		setClientMaxBodySizeData(value, hostData);
	} else if (key == "location") {
		// TODO
		setLocationWayData(value, hostData);
	} else if (key == "...") {
		// TODO
		setLocationDetailsData(value, hostData);
	}
}

/*
**	Set host and port data to HostData structure
** 	TODO: Validation
*/

void	ParserConfig::setListenData(std::string data, HostData *hostData) {
	const int delim = data.find_first_of(':');
	const char *port;
	char *remainder;

	if (!(delim > 0 && delim < data.size())) {
		std::cout << "Error!!!" << std::endl;
	}

	hostData->host = data.substr(0, delim);
	port = data.substr(delim + 1, data.length()).c_str();
	hostData->port = std::strtoll(port, &remainder, 0);
	if (!isSomeSymbolInTheEnd(remainder, ';')) {
		std::cout << "error!" << std::endl;
	}
	// std::cout << data << std::endl;
}

/*
**	Set serverName to HostData structure
*/

void	ParserConfig::setServerNameData(std::string data, HostData *hostData) {
	if (isSomeSymbolInTheEnd(data, ';')) {
		hostData->serverName = data.substr(0, data.length() - 1);
	}
	// std::cout << data << std::endl;
}

/*
**	Set root to HostData structure
*/

void	ParserConfig::setRootData(std::string data, HostData *hostData) {
	if (isSomeSymbolInTheEnd(data, ';')) {
		hostData->root = data.substr(0, data.length() - 1);
	}
	// std::cout << data << std::endl;
}

/*
**	Set errorPage to HostData structure
*/

void	ParserConfig::setErrorPageData(std::string data, HostData *hostData) {
	const int delim = data.find_first_of(' ');
	const char *port;
	char *remainder;

	if (isSomeSymbolInTheEnd(data, ';')) {
		port = data.substr(0, delim).c_str();
		hostData->errorPage.errorNumber = std::strtoll(port, &remainder, 0);
		hostData->errorPage.locationOfErrorPage = data.substr(delim + 1, data.length() - delim - 2);
	}
	// std::cout << data << std::endl;
}

/*
**	Set clientMaxBodySize to HostData structure
*/

void	ParserConfig::setClientMaxBodySizeData(std::string data, HostData *hostData) {
	if (isSomeSymbolInTheEnd(data, ';')) {
		hostData->clientMaxBodySize = data.substr(0, data.length() - 1);
	}
	// std::cout << data << std::endl;
}

/*
**	Set location->way to HostData structure
*/

void	ParserConfig::setLocationWayData(std::string data, HostData *hostData) {
	Location location;

	if (isSomeSymbolInTheEnd(data, ':')) {
		location.way = data.substr(0, data.length() - 1);
		hostData->location.push_back(location);
	}
	// std::cout << data << std::endl;
}

/*
**	Set location detaits (Location structure) to HostData structure
*/

void	ParserConfig::setLocationDetailsData(std::string data, HostData *hostData) {
	std::string key;
	std::string value;
	int	currentLocation;

	if (isSomeSymbolInTheEnd(data, ';')) {
		currentLocation = hostData->location.size();
		splitFirstArgiment(data, &key, &value);
		if (key == "root") {
			setRootDataToLocation(value, hostData, currentLocation);
		} else if (key == "methods") {
			setMethodsToLocation(value, hostData, currentLocation);
		} else if (key == "autoindex") {
			setAutoindexToLocation(value, hostData, currentLocation);
		} else if (key == "index") {
			setIndexToLocation(value, hostData, currentLocation);
		} else if (key == "upload_enable") {
			setUploadEnableToLocation(value, hostData, currentLocation);
		} else if (key == "upload_path") {
			setUploadPathToLocation(value, hostData, currentLocation);
		} else if (key == "cgi_extencion") {
			setCgiExtencionToLocation(value, hostData, currentLocation);
		} else if (key == "cgi_path") {
			setCgiPathToLocation(value, hostData, currentLocation);
		}
	}
	// std::cout << data << std::endl;
}

/*
**	Split each string of config to key and value. Send to enterDataToHostDataStruct function key and value.
*/

void	ParserConfig::devideConfigToComponents(std::list<std::string> config, HostData *hostData) {
	std::list<std::string>::iterator it = config.begin();
	std::string key;
	std::string value;

	for (; it != config.end(); it++) {
		splitFirstArgiment(*it, &key, &value);
		// std::cout << "Key: \t|" << key << "|\nValue: \t|" << value << "|\n" << std::endl;
		enterDataToHostDataStruct(key, value, hostData);
	}
}

void	ParserConfig::setRootDataToLocation(std::string data, 
		HostData *hostData, int currentLocation) {
	hostData->location[currentLocation].root = data.substr(0, data.length() - 1);
}

void	ParserConfig::setMethodsToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	std::vector<std::string> methods;
	std::vector<std::string>::iterator it;

	methods = split(data);
	it = methods.begin();
	// hostData->location[currentLocation].httpMethods = methods;
	for (; it != methods.end(); it++) {
		std::cerr << hostData->location[currentLocation].root << std::endl;
		// hostData->location[currentLocation].httpMethods.push_back("123");
		// hostData->location[currentLocation].httpMethods->push_back(*it);
	}
}

void	ParserConfig::setAutoindexToLocation(std::string data, 
		HostData *hostData, int currentLocation){

}

void	ParserConfig::setIndexToLocation(std::string data, 
		HostData *hostData, int currentLocation){

}

void	ParserConfig::setUploadEnableToLocation(std::string data, 
		HostData *hostData, int currentLocation){

}

void	ParserConfig::setUploadPathToLocation(std::string data, 
		HostData *hostData, int currentLocation){

}

void	ParserConfig::setCgiExtencionToLocation(std::string data, 
		HostData *hostData, int currentLocation){

}

void	ParserConfig::setCgiPathToLocation(std::string data, 
		HostData *hostData, int currentLocation){

}


/*
**	Custom exception for config parser
*/

const char	*ParserConfig::ParserConfigException::what() const throw() {
	return "Parcer error";
}
