#include "ParserConfig.hpp"

ParserConfig::ParserConfig() {}

Config* ParserConfig::parse(char* configFilePath) {
	std::vector<HostData*> hosts;
	Config *config = new Config();
	std::list<std::string> configFile;
	try {
		readConfigFile(configFilePath, &configFile);
		hosts = devideConfigToComponents(configFile);
		for (int i = 0; i < hosts.size(); i++) {
			std::cout << "Port parse: " << hosts[i]->port << std::endl;
		}
		

		// /*		STDOUT OF HOST		*/
		// std::cout << "host: \t\t\t" << hostData.host << std::endl;
		// std::cout << "port: \t\t\t" << hostData.port << std::endl;
		// std::cout << "serverName: \t\t" << hostData.serverName << std::endl;
		// std::cout << "root: \t\t\t" << hostData.root << std::endl;
		// // std::cout << "error page - err num: \t" << hostData.errorPage.errorNbr << std::endl;
		// // std::cout << "error page - location: \t" << hostData.errorPage.errorPagePath << std::endl;
		// std::cout << "client max body size: \t" << hostData.clientMaxBodySize << std::endl;

		// /*		STDOUT OF ERROR PAGES		*/
		// std::vector<ErrorPage*>::iterator it = hostData.errorPage.begin();
		// for (; it != hostData.errorPage.end(); it++) {
		// 	std::cout << "Error page: \t\t";
		// 	std::cout << (*it)->errorNbr << " ";
		// 	std::cout << (*it)->errorPagePath << std::endl;
		// }
		// std::cout << std::endl;

		// /*		STDOUT OF LOCATION DETAILS		*/
		// for (int i = 0; i < hostData.location.size(); i++) {
		// 	std::cout << "\033[1m\033[31m" << "Location: " << i  << "\033[0m" << std::endl;
		// 	std::cout << "way: \t\t\t" << hostData.location[i]->way << std::endl;
		// 	std::cout << "root: \t\t\t" << hostData.location[i]->root << std::endl;
		// 	std::cout << "authoindex: \t\t" << hostData.location[i]->autoindex << std::endl;

		// 	/*		STDOUT OF METHODS		*/
		// 	std::vector<std::string>::iterator it1 = hostData.location[i]->httpMethods.begin();
		// 	std::cout << "Methods: \t\t";
		// 	for (; it1 != hostData.location[i]->httpMethods.end(); it1++) {
		// 		std::cout << *it1 << " ";
		// 	}
		// 	std::cout << std::endl;

		// 	/*		STDOUT OF INDEX		*/
		// 	std::vector<std::string>::iterator it2 = hostData.location[i]->index.begin();
		// 	std::cout << "Index: \t\t\t";
		// 	for (; it2 != hostData.location[i]->index.end(); it2++) {
		// 		std::cout << *it2 << " ";
		// 	}
		// 	std::cout << std::endl;

		// 	std::cout << "upload enable: \t\t" << hostData.location[i]->uploadEnable << std::endl;
		// 	std::cout << "upload path: \t\t" << hostData.location[i]->uploadPath << std::endl;
		// 	std::cout << "cgi extension: \t\t" << hostData.location[i]->cgiextension << std::endl;
		// 	std::cout << "cgi path: \t\t" << hostData.location[i]->cgiPath << std::endl;
		// 	std::cout << std::endl;
		// }

	} catch (std::exception& e) {
		// std::cerr << e.what() << std::endl;
	}

	for (int i = 0; i < hosts.size(); i++) {
		Host *host = new Host(hosts[i]);
		config->addNewHost(host);
	}

	return config;
}

/*
**	Reading config file to list
*/

void	ParserConfig::readConfigFile(char *configFilePath, std::list<std::string> *config) {
	std::ifstream input;
	std::string buf;

	input.open(configFilePath);
	if (!input.is_open()) {
		throw ParserConfigException("File open error");
	}
	while (std::getline(input, buf)) {
		(*config).push_back(buf);
	}
	input.close();
}

/*
**	Split each string of config to key and value. Send to enterDataToHostDataStruct function key and value.
*/

std::vector<HostData*>	ParserConfig::devideConfigToComponents(std::list<std::string> config) {
	std::list<std::string>::iterator it = config.begin();
	std::vector<HostData*> hosts;
	HostData *hostData = new HostData;
	std::string key;
	std::string value;

	setDefaultHostValues(hostData);
	for (; it != config.end(); it++) {
		splitFirstArgiment(*it, &key, &value);
		if (key == "***") {
			std::cout << "New host" << std::endl;
			hosts.push_back(hostData);
			std::cout << "before: " << hostData->host << std::endl;
			hostData = new HostData;
			std::cout << "after: " << hostData->host << std::endl;
			// setDefaultHostValues(hostData);
		} else {
			enterDataToHostDataStruct(key, value, hostData);
		}
	}
	hosts.push_back(hostData);
	for (int i = 0; i < hosts.size(); i++) {
		std::cout << "Port parseConfig: " << hosts[i]->port << std::endl;
	}
	return hosts;
}

void	ParserConfig::setDefaultHostValues(HostData *hostData) {
	hostData->ip = "";
	hostData->host = "";
	hostData->serverName = "";
	hostData->port = 0;
	hostData->root = "";
	hostData->errorPage.clear();
	hostData->clientMaxBodySize = "";
	hostData->location.clear();
}

/*
**	Check and enter data to HostData structure
*/

void	ParserConfig::enterDataToHostDataStruct(std::string const &key, std::string const &value, HostData *hostData) {
	std::cout << key << " " << value << std::endl;
	try {
		if (isSomeSymbolInTheEnd(value, ';')) {
			if (key == "listen") {
				setListenData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "server_name") {
				setServerNameData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "root") {
				setRootData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "error_page") {
				setErrorPageData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "client_max_body_size") {
				setClientMaxBodySizeData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "...") {
				setLocationDetailsData(value.substr(0, value.length() - 1), hostData);
			} else {
				throw ParserConfigException("enterDataToHostDataStruct error");
			}
		} else if (isSomeSymbolInTheEnd(value, ':')) {
			if (key == "location") {
				setLocationWayData(value.substr(0, value.length() - 1), hostData);
			} else {
				throw ParserConfigException("enterDataToHostDataStruct error");
			}
		} else if (key.length() > 0) {
			throw ParserConfigException("enterDataToHostDataStruct error");
		}
	} catch (ParserConfigException e) {
		std::cerr << "Parser error: " << e.what() << std::endl;
		throw e;
	}
}

void	ParserConfig::setHostToServer(HostData *hostData, std::vector<HostData*> hosts) {
	if (hostData->host.size() > 0 && hostData->port > 0) {
		HostData *host = new HostData();
		host = hostData;
	} else {
		throw ParserConfigException("setHostToServer error");
	}
}


/*
**	Set location detaits (Location structure) to HostData structure
*/

void	ParserConfig::setLocationDetailsData(std::string data, HostData *hostData) {
	std::string key;
	std::string value;
	int	currentLocation;

	currentLocation = hostData->location.size() - 1;
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
	} else if (key == "cgi_extension") {
		setCgiExtensionToLocation(value, hostData, currentLocation);
	} else if (key == "cgi_path") {
		setCgiPathToLocation(value, hostData, currentLocation);
	} else {
		throw ParserConfigException("setLocationDetailsData error");
	}
}

/*
**	Set host and port data to HostData structure
*/

void	ParserConfig::setListenData(std::string data, HostData *hostData) {
	std::string	host;
	int			delim;
	const char	*tmp;
	size_t		port;
	char		*remainder;

	delim = data.find_first_of(':');
	if (delim == std::string::npos) {
		throw ParserConfigException("setListenData error");
	} else {
		host = data.substr(0, delim);
		tmp = data.substr(delim + 1, data.length()).c_str();
		port = std::strtoll(tmp, &remainder, 0);
		if (!remainder[0]) {
			hostData->host = host;
			hostData->port = port;
		} else {
			throw ParserConfigException("setListenData error");
		}
	}
}

/*
**	Set serverName to HostData structure
*/

void	ParserConfig::setServerNameData(std::string data, HostData *hostData) {
	hostData->serverName = data;
}

/*
**	Set root to HostData structure
*/

void	ParserConfig::setRootData(std::string data, HostData *hostData) {
	if (data.find_first_of("/") == 0) {
		hostData->root = data;
	} else {
		throw ParserConfigException("setRootData error");
	}
}

/*
**	Set errorPage to HostData structure
*/

void	ParserConfig::setErrorPageData(std::string data, HostData *hostData) {
	int			delim;
	size_t		errorNbr;
	std::string	errorPagePath;
	const char	*port;
	ErrorPage*	errorPage = new ErrorPage();
	size_t		currentErrorPage;

	currentErrorPage = hostData->errorPage.size();
	delim = data.find_first_of(' ');
	if (delim != std::string::npos) {
		port = data.substr(0, delim).c_str();
		errorNbr = std::strtoll(port, NULL, 0);
		errorPagePath = data.substr(delim + 1, data.length() - delim - 1);
		if (errorPagePath.find_first_of(' ') == std::string::npos) {
			errorPage->errorNbr = errorNbr;
			errorPage->errorPagePath = errorPagePath;
			if (errorPagePath.find_first_of("/") == 0 && errorNbr != 0) {
				hostData->errorPage.push_back(errorPage);
			} else {
				throw ParserConfigException("setErrorPageData error");
			}
		} else {
			throw ParserConfigException("setErrorPageData error");
		}
	} else {
		throw ParserConfigException("setErrorPageData error");
	}
}

/*
**	Set clientMaxBodySize to HostData structure
*/

void	ParserConfig::setClientMaxBodySizeData(std::string data, HostData *hostData) {
	hostData->clientMaxBodySize = data;
}

/*
**	Set location->way to HostData structure
*/

void	ParserConfig::setLocationWayData(std::string data, HostData *hostData) {
	Location *location = new Location();

	if (data.find_first_of("/") == 0) {
		location->way = data;
		hostData->location.push_back(location);
	} else {
		throw ParserConfigException("setRootData error");
	}
}

/*
**	Set location->root to HostData structure
*/

void	ParserConfig::setRootDataToLocation(std::string data, 
		HostData *hostData, int currentLocation) {
	if (data.find_first_of("/") == 0) {
		hostData->location[currentLocation]->root = data;
	} else {
		throw ParserConfigException("setRootDataToLocation error");
	}
}
/*
**	Set location->methods vector to HostData structure
*/

void	ParserConfig::setMethodsToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	std::vector<std::string> methods;
	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2;

	methods = split(data, " ");
	hostData->location[currentLocation]->httpMethods = methods;
	it1 = methods.begin();
	it2 = hostData->location[currentLocation]->httpMethods.begin();
	for (; it1 != methods.end(); it1++, it2++) {
		it2 = it1;
	}
}

/*
**	Set location->autoindex to HostData structure
*/

void	ParserConfig::setAutoindexToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	if (data == "on") {
		hostData->location[currentLocation]->autoindex = true;
	} else if (data == "off") {
		hostData->location[currentLocation]->autoindex = false;
	} else {
		throw ParserConfigException("setAutoindexToLocation error");
	}

}

/*
**	Set location->index vector to HostData structure
*/

void	ParserConfig::setIndexToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	std::vector<std::string> index;
	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2;

	index = split(data, " ");
	hostData->location[currentLocation]->index = index;
	it1 = index.begin();
	it2 = hostData->location[currentLocation]->index.begin();
	for (; it1 != index.end(); it1++, it2++) {
		it2 = it1;
	}
}

/*
**	Set location->upload_enable to HostData structure
*/

void	ParserConfig::setUploadEnableToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	if (data == "on") {
		hostData->location[currentLocation]->uploadEnable = true;
	} else if (data == "off") {
		hostData->location[currentLocation]->uploadEnable = false;
	} else {
		throw ParserConfigException("setUploadEnableToLocation error");
	}
}

/*
**	Set location->upload_path to HostData structure
*/

void	ParserConfig::setUploadPathToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	if (data.find_first_of("/") == 0) {
		hostData->location[currentLocation]->uploadPath = data;
	} else {
		throw ParserConfigException("setUploadPathToLocation error");
	}
}

/*
**	Set location->cgi_extension to HostData structure
*/

void	ParserConfig::setCgiExtensionToLocation(std::string data, 
		HostData *hostData, int currentLocation){
}

/*
**	Set location->cgi_path to HostData structure
*/

void	ParserConfig::setCgiPathToLocation(std::string data, 
		HostData *hostData, int currentLocation){
	if (data.find_first_of("/") == 0) {
		hostData->location[currentLocation]->cgiPath = data;
	} else {
		throw ParserConfigException("setCgiPathToLocation error");
	}
}