#include "ParserConfig.hpp"
#include "ResponseTypes.hpp"
#include <CGI.hpp>

ParserConfig::ParserConfig() {
	_cgi = new CgiParser;
}

ParserConfig::~ParserConfig() {
	delete _cgi;
}

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
		cleanUpHost(hosts[i]);
	}
	return config;
}

void	ParserConfig::cleanUpHost(HostData *hostData) {
	std::vector<ErrorPage*>::iterator errorPageIt = hostData->errorPage.begin();
	for (; errorPageIt != hostData->errorPage.end(); errorPageIt++) {
		delete *errorPageIt;
	}
	std::vector<Location*>::iterator locationIt = hostData->location.begin();
	int i = 0;
	for (; locationIt != hostData->location.end(); locationIt++, i++) {
		if ((*locationIt)->cgi) {
			delete (*locationIt)->cgi;
		}
	}
	delete hostData;
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

	try {
		it = config.begin();
		bool isLocation = false;

		hostData = new HostData;
		setDefaultHostValues(hostData);

		for (; it != config.end(); it++) {
			splitFirstArgiment(*it, &key, &value);
			if (value.find_first_not_of(' ') != 0 && 
				value.find_first_not_of(' ') != std::string::npos) {
				throw ParserConfigException("devideConfigToComponents error");
			}
			if (key == "***") {
				if (hostData->ip.size() > 0 && hostData->port > 0) {

					hosts.push_back(hostData);
					hostData = new HostData;
					setDefaultHostValues(hostData);
				} else {
					throw ParserConfigException("devideConfigToComponents error");
				}
			} else {
				enterDataToHostDataStruct(key, value, hostData, &isLocation);
			}
		}
		hosts.push_back(hostData);
		return hosts;
	} catch(const std::exception& e) {
		throw e;
	}
}

void	ParserConfig::setDefaultHostValues(HostData *hostData) {
	hostData->ip = "";
	hostData->serverName = "";
	hostData->port = 0;
	hostData->root = "/";
	hostData->errorPage.clear();
	hostData->clientMaxBodySize = 0;
	hostData->location.clear();

	for (int i = 0; arrResponseStatuses[i].first ; i++){
		if (arrResponseStatuses[i].first >= 400) {
			Location *newLocation = new Location;
			newLocation->root = "/";
			newLocation->way = DEFAULT_ERROR_PAGE_PATH + std::to_string(arrResponseStatuses[i].first) + ".html";
			hostData->location.push_back(newLocation);
		}
	}
}

void	ParserConfig::setLocationDefaultValue(Location *location) {
	_cgi->path = "";
	_cgi->extension = "";
	
	location->root = "";
	location->redirectStatusCode = 0;
	location->redirectPath = "";
	location->httpMethods.clear();
	location->index.clear();
	location->autoindex = false;
	location->uploadEnable = false;
	location->uploadPath = "";
	location->cgi = NULL;
}

/*
**	Check and enter data to HostData structure
*/

void	ParserConfig::enterDataToHostDataStruct(std::string const &key, std::string const &value,
		HostData *hostData, bool *isLocation) {
	try {
		if (isSomeSymbolInTheEnd(value, ';')) {
			if (key == "listen") {
				*isLocation = false;
				setListenData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "server_name") {
				*isLocation = false;
				setServerNameData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "root") {
				*isLocation = false;
				setRootData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "error_page") {
				*isLocation = false;
				setErrorPageData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "client_max_body_size") {
				*isLocation = false;
				setClientMaxBodySizeData(value.substr(0, value.length() - 1), hostData);
			} else if (key == "..." && *isLocation) {
				setLocationDetailsData(value.substr(0, value.length() - 1), hostData);
			} else {
				throw ParserConfigException("enterDataToHostDataStruct error");
			}
		} else if (isSomeSymbolInTheEnd(value, ':')) {
			if (key == "location") {
				*isLocation = true;
				setLocationWayData(value.substr(0, value.length() - 1), hostData);
				setLocationDefaultValue(hostData->location[hostData->location.size() - 1]);
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
		setRedirectToLocation(value, hostData->location[currentLocation]);
	} else if (key == "root") {
		setRootDataToLocation(value, hostData->location[currentLocation]);
	} else if (key == "methods") {
		setMethodsToLocation(value, hostData->location[currentLocation]);
	} else if (key == "autoindex") {
		setAutoindexToLocation(value, hostData->location[currentLocation]);
	} else if (key == "index") {
		setIndexToLocation(value, hostData->location[currentLocation]);
	} else if (key == "upload_enable") {
		setUploadEnableToLocation(value, hostData->location[currentLocation]);
	} else if (key == "upload_path") {
		setUploadPathToLocation(value, hostData->location[currentLocation]);
	} else if (key == "cgi_extension") {
		setCgiParserData(value, "extension", hostData, hostData->location[currentLocation]);
	} else if (key == "cgi_path") {
		setCgiParserData(value, "path", hostData, hostData->location[currentLocation]);
	} else {
		throw ParserConfigException("setLocationDetailsData error");
	}

	if (_cgi->path.length() && _cgi->extension.length() &&
		!hostData->location[hostData->location.size() - 1]->cgi) {
		CGI* cgi = new CGI(_cgi->path, _cgi->extension, _cgi->root, _cgi->ip, _cgi->port);
		hostData->location[hostData->location.size() - 1]->cgi = cgi;
		// delete _cgi;
	} else {
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
	
			errorPage = new ErrorPage;
			errorPage->errorNbr = errorNbr;
			errorPage->errorPagePath = errorPagePath;
			hostData->errorPage.push_back(errorPage);
			Location *location = new Location;
			location->root = hostData->root;
			location->way = errorPagePath;
			hostData->location.push_back(location);
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

void	ParserConfig::setRedirectToLocation(std::string data, Location *location) {
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
			((redirectPath.find_first_of("/") == 0 && statusCode != 0) ||
			(redirectPath.find("http") == 0 && statusCode != 0))) {

			location->redirectStatusCode = statusCode;
			location->redirectPath = redirectPath;
		} else {
			throw ParserConfigException("setErrorPageData error");
		}
	} else {
		throw ParserConfigException("setErrorPageData error");
	}
}

/*
**	Set location->way to HostData structure
*/

void	ParserConfig::setLocationWayData(std::string data, HostData *hostData) {
	Location	*location;

	if (data.find_first_of("/") == 0) {
		location = new Location;
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
		Location *location) {
	if (data.find_first_of("/") == 0) {
		location->root = data;
	} else {
		throw ParserConfigException("setRootDataToLocation error");
	}
}
/*
**	Set location->methods vector to HostData structure
*/

void	ParserConfig::setMethodsToLocation(std::string data, 
		Location *location){
	std::vector<std::string>::iterator	it1;
	std::vector<std::string>::iterator	it2;
	std::vector<std::string>			methods;

	methods = split(data, " ");
	location->httpMethods = methods;
	it1 = methods.begin();
	it2 = location->httpMethods.begin();
	for (; it1 != methods.end(); it1++, it2++) {
		it2 = it1;
	}
}

/*
**	Set location->autoindex to HostData structure
*/

void	ParserConfig::setAutoindexToLocation(std::string data, 
		Location *location){
	if (data == "on") {
		location->autoindex = true;
	} else if (data == "off") {
		location->autoindex = false;
	} else {
		throw ParserConfigException("setAutoindexToLocation error");
	}

}

/*
**	Set location->index vector to HostData structure
*/

void	ParserConfig::setIndexToLocation(std::string data, 
		Location *location){
	std::vector<std::string>::iterator	it1;
	std::vector<std::string>::iterator	it2;
	std::vector<std::string>			index;

	index = split(data, " ");
	location->index = index;
	it1 = index.begin();
	it2 = location->index.begin();
	for (; it1 != index.end(); it1++, it2++) {
		it2 = it1;
	}
}

/*
**	Set location->upload_enable to HostData structure
*/

void	ParserConfig::setUploadEnableToLocation(std::string data, 
		Location *location){
	if (data == "on") {
		location->uploadEnable = true;
	} else if (data == "off") {
		location->uploadEnable = false;
	} else {
		throw ParserConfigException("setUploadEnableToLocation error");
	}
}

/*
**	Set location->upload_path to HostData structure
*/

void	ParserConfig::setUploadPathToLocation(std::string data, 
		Location *location){
	if (data.find_first_of("/") == 0) {
		location->uploadPath = data;
	} else {
		throw ParserConfigException("setUploadPathToLocation error");
	}
}

void	ParserConfig::setCgiParserData(std::string data, std::string type, HostData *hostData, Location *location) {
	if (type == "path" && data.find_first_of("/") == 0) {
		_cgi->path = data;
	} else if (type == "extension" && data == "php") {
		_cgi->extension = data;
	}

	if (!_cgi->root.length() && location->root.length()) {
		_cgi->root = location->root;
	} else {
		_cgi->root = hostData->root;
	}
	
	if (hostData->ip.length() && hostData->port && !_cgi->port.length() && !_cgi->ip.length()) {
		std::string port_str = std::to_string(static_cast<int>(hostData->port));
		_cgi->port = port_str;
		_cgi->ip = hostData->ip;
	}
}