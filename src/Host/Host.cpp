#include "Host.hpp"
#include "CGI.hpp"

Host::Host(HostData *hostData) {
	if (_data != hostData) {
		_data = new HostData;
		_data->ip = hostData->ip;
		_data->port = hostData->port;
		_data->serverName = hostData->serverName;
		_data->root = hostData->root;
		_data->clientMaxBodySize = hostData->clientMaxBodySize;

		std::vector<ErrorPage*>::iterator errorPageIt = hostData->errorPage.begin();
		for (; errorPageIt != hostData->errorPage.end(); errorPageIt++) {
			ErrorPage *errorPage = new ErrorPage;
			errorPage->errorNbr = (*errorPageIt)->errorNbr;
			errorPage->errorPagePath = (*errorPageIt)->errorPagePath;
			_data->errorPage.push_back(errorPage);
		}

		std::vector<Location*>::iterator locationIt = hostData->location.begin();
		int i = 0;
		for (; locationIt != hostData->location.end(); locationIt++, i++) {
			Location *location = new Location;
			location->way = (*locationIt)->way;
			location->root = (*locationIt)->root;
			location->redirectStatusCode = (*locationIt)->redirectStatusCode;
			location->redirectPath = (*locationIt)->redirectPath;

			std::vector<std::string>::iterator methods = (*locationIt)->httpMethods.begin();
			for (; methods != (*locationIt)->httpMethods.end(); methods++) {
				location->httpMethods.push_back(*methods);
			}
			if (!(*locationIt)->index.empty()) {
				std::vector<std::string>::iterator index = (*locationIt)->index.begin();
				for (; index != (*locationIt)->index.end(); index++) {
					location->index.push_back(*index);
				}
			}

			if ((*locationIt)->cgi) {
				location->cgi = new CGI(*(*locationIt)->cgi);
			} else {
				location->cgi = NULL;
			}

			location->autoindex = (*locationIt)->autoindex;
			location->uploadEnable = (*locationIt)->uploadEnable;
			location->uploadPath = (*locationIt)->uploadPath;

			_data->location.push_back(location);
		} 
	} else {
		_data = hostData;
	}
}

Host::~Host() {
	std::vector<ErrorPage*>::iterator errorPageIt = _data->errorPage.begin();
	for (; errorPageIt != _data->errorPage.end(); errorPageIt++) {
		delete *errorPageIt;
	}
	std::vector<Location*>::iterator locationIt = _data->location.begin();
	int i = 0;
	for (; locationIt != _data->location.end(); locationIt++, i++) {
		if ((*locationIt)->cgi) {
			delete (*locationIt)->cgi;
		}
		delete *locationIt;
	}
	delete _data;
}

Host::Host(std::string ip, size_t port, std::string serverName) {
	_data = new HostData;
	_data->ip = ip;
	_data->port = port;
	_data->serverName = serverName;
}

Host::Host(const Host& other) {
}

std::string		Host::getIp() const {
	return _data->ip;
}

size_t		Host::getPort() const {
	return _data->port;
}

std::string	Host::getServerName() const {
	return _data->serverName;
}

HostData*	Host::getData() const {
	return _data;
}

bool operator==(const Host &lhs, const Host &rhs) {
	if (lhs.getIp() != rhs.getIp()
		|| lhs.getPort() != rhs.getPort()
		|| lhs.getServerName() != rhs.getServerName()){
		return false;
	}
	return true;
}
