#include "ParserConfig.hpp"
#include <CGI.hpp>

ParserConfig::ParserConfig() {}

Config* ParserConfig::parse(char* configFilePath) {
	std::list<std::string>	configFile;
	std::vector<HostData*>	hosts;
	Config					*config;

	try {
		readConfigFile(configFilePath, &configFile);
		hosts = devideConfigToComponents(configFile);
	} catch (std::exception& e) {
		throw e;
	}

	config = new Config();
	for (int i = 0; i < hosts.size(); i++) {
		Host *host = new Host(hosts[i]);
		config->addNewHost(host);
		// delete hosts[i];
	}
	return config;
}

/*
**	Reading config file to list
*/

void	ParserConfig::readConfigFile(char *configFilePath, std::list<std::string> *config) {
	std::ifstream	input;
	std::string		buf;

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
	std::list<std::string>::iterator	it;
	std::vector<HostData*>				hosts;
	std::string							key;
	std::string							value;
	HostData							*hostData;

	hostData = new HostData;
	it = config.begin();
	setDefaultHostValues(hostData);
	try {
		for (; it != config.end(); it++) {
			splitFirstArgiment(*it, &key, &value);
			if (value.find_first_not_of(' ') != 0 && 
				value.find_first_not_of(' ') != std::string::npos) {
				throw ParserConfigException("devideConfigToComponents error");
			}
			if (key == "***") {
				if (hostData->ip.size() > 0 && hostData->port > 1023 && hostData->port < 65536) {
					hosts.push_back(hostData);
					hostData = new HostData;
					setDefaultHostValues(hostData);
				} else {
					throw ParserConfigException("devideConfigToComponents error");
				}
			} else {
				enterDataToHostDataStruct(key, value, hostData);
			}
		}
		hosts.push_back(hostData);
		return hosts;
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw e;
	}
}

void	ParserConfig::setDefaultHostValues(HostData *hostData) {
	
	hostData->ip = "";
	hostData->serverName = "";
	hostData->port = 0;
	hostData->root = "";
	hostData->errorPage.clear();
	hostData->clientMaxBodySize = 0;
	std::vector<Location*>::iterator it = hostData->location.begin();
	for (; it != hostData->location.end(); it++) {
		(*it)->way = "";
		(*it)->root = "";
		(*it)->redirect->statusCode = 0;
		(*it)->redirect->path = "";
		(*it)->httpMethods.clear();
		(*it)->index.clear();
		(*it)->autoindex = false;
		(*it)->uploadEnable = false;
		(*it)->uploadPath = "";
		(*it)->cgi->setPath("");
		(*it)->cgi->setRoot("");
		(*it)->cgi->setExtension("");
	}
	hostData->location.clear();
}

/*
**	Check and enter data to HostData structure
*/

void	ParserConfig::enterDataToHostDataStruct(std::string const &key, std::string const &value, HostData *hostData) {
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

/*
**	Set location detaits (Location structure) to HostData structure
*/

void	ParserConfig::setLocationDetailsData(std::string data, HostData *hostData) {
	std::string	key;
	std::string	value;
	int			currentLocation;
	int			cgiFullInfo;

	currentLocation = hostData->location.size() - 1;
	splitFirstArgiment(data, &key, &value);
	if (key == "return") {
		setRedirectToLocation(value, hostData, currentLocation);
	} else if (key == "root") {
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
		setCgiRootToLocation(hostData, currentLocation);
	} else {
		throw ParserConfigException("setLocationDetailsData error");
	}
}

/*
**	Set host and port data to HostData structure
*/

void	ParserConfig::setListenData(std::string data, HostData *hostData) {
	std::string	ip;
	int			delim;
	const char	*tmp;
	size_t		port;
	char		*remainder;

	delim = data.find_first_of(':');
	
	if (delim == std::string::npos) {
		throw ParserConfigException("setListenData error");
	} else {
		ip = data.substr(0, delim);
		tmp = data.substr(delim + 1, data.length()).c_str();
		port = std::strtoll(tmp, &remainder, 0);

		if (!remainder[0]) {
			hostData->ip = ip;
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
	const char	*port;
	std::string	errorPagePath;
	ErrorPage	*errorPage;
	size_t		errorNbr;
	size_t		currentErrorPage;

	currentErrorPage = hostData->errorPage.size();
	delim = data.find_first_of(' ');

	if (delim != std::string::npos) {
		
		port = data.substr(0, delim).c_str();
		errorNbr = std::strtoll(port, NULL, 0);
		errorPagePath = data.substr(delim + 1, data.length() - delim - 1);

		if (errorPagePath.find_first_of(' ') == std::string::npos &&
			errorPagePath.find_first_of("/") == 0 && errorNbr != 0) {
	
			errorPage = new ErrorPage();
			errorPage->errorNbr = errorNbr;
			errorPage->errorPagePath = errorPagePath;
			hostData->errorPage.push_back(errorPage);
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
	for (int i = 0; i < data.length() - 1; i++) {
		if (data[i] >= '0' && data[i] <= '9') {
			continue;
		} else {
			throw ParserConfigException("setClientMaxBodySizeData error");
		}
	}
	if (data[data.length() - 1] == 'M') {
		hostData->clientMaxBodySize = atoll(data.c_str()) * pow(1024, 2);
	} else if (data[data.length() - 1] == 'K') {
		hostData->clientMaxBodySize = atoll(data.c_str()) * 1024;
	} else {
		throw ParserConfigException("setClientMaxBodySizeData error");
	}
}

void	ParserConfig::setRedirectToLocation(std::string data, HostData *hostData, int currentLocation) {
	Redirect *redirect;
	int delim;
	const char *tmp;
	size_t statusCode;
	std::string redirectPath;

	delim = data.find_first_of(' ');

	if (delim != std::string::npos) {

		tmp = data.substr(0, delim).c_str();
		statusCode = std::strtoll(tmp, NULL, 0);
		redirectPath = data.substr(delim + 1, data.length() - delim - 1);

		if (redirectPath.find_first_of(' ') == std::string::npos &&
			redirectPath.find_first_of("/") == 0 && statusCode != 0) {

			Redirect *redirect = new Redirect;
			redirect->statusCode = statusCode;
			redirect->path = redirectPath;
			hostData->location[currentLocation]->redirect = redirect;
		} else {
			throw ParserConfigException("setErrorPageData error");
		}
	} else {
		throw ParserConfigException("setErrorPageData error");
	}
	// hostData->location[currentLocation]->redirect
}

/*
**	Set location->way to HostData structure
*/

void	ParserConfig::setLocationWayData(std::string data, HostData *hostData) {
	Location	*location;

	if (data.find_first_of("/") == 0) {
		location = new Location();
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
	std::vector<std::string>::iterator	it1;
	std::vector<std::string>::iterator	it2;
	std::vector<std::string>			methods;

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
	std::vector<std::string>::iterator	it1;
	std::vector<std::string>::iterator	it2;
	std::vector<std::string>			index;

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

void	ParserConfig::setCgiExtensionToLocation(std::string data, HostData *hostData, int currentLocation) {
	if (data == "php") {
		if (hostData->location[currentLocation]->cgi == NULL) {
			hostData->location[currentLocation]->cgi = new CGI();
		}
		hostData->location[currentLocation]->cgi->setExtension(data);
	} else {
		throw ParserConfigException("setCgiExtensionToLocation error");
	}
}

/*
**	Set location->cgi_path to HostData structure
*/

void	ParserConfig::setCgiPathToLocation(std::string data, HostData *hostData, int currentLocation) {
	if (data.find_first_of("/") == 0) {
		if (hostData->location[currentLocation]->cgi == NULL) {
			hostData->location[currentLocation]->cgi = new CGI();
		}
		hostData->location[currentLocation]->cgi->setPath(data);
	} else {
		throw ParserConfigException("setCgiPathToLocation error");
	}
}

void	ParserConfig::setCgiRootToLocation(HostData *hostData, int currentLocation) {
	std::string serverRoot = hostData->root;
	std::string hostRoot = hostData->location[currentLocation]->root;
	hostData->location[currentLocation]->cgi->setRoot(serverRoot + hostRoot);
}