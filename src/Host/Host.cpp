#include "Host.hpp"

Host::Host(HostData *hostData) {
	_data = hostData;
	// if ((*this)._data != hostData) {
	// 	(*this)._data = new HostData;
	// 	(*this)._data->ip = hostData->ip;
	// 	(*this)._data->serverName = hostData->serverName;
	// 	(*this)._data->port = hostData->port;
	// 	(*this)._data->errorPage = hostData->errorPage;
	// 	(*this)._data->clientMaxBodySize = hostData->clientMaxBodySize;
	// 	(*this)._data->location = hostData->location;
	// }
}

Host::Host(std::string ip, size_t port, std::string serverName) {
	_data = new HostData;
	_data->ip = ip;
	_data->port = port;
	_data->serverName = serverName;
}

Host::Host(const Host& other) {}

std::string		Host::getIp() const {
	return _data->ip;
}

size_t			Host::getPort() const {
	return _data->port;
}

std::string		Host::getServerName() const {
	return _data->serverName;
}

HostData* 	Host::getData() const {
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
