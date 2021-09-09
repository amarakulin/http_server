#include "Host.hpp"

Host::Host(HostData *hostData) : _data(hostData) {}

Host::Host(std::string ip, size_t port, std::string serverName) {
	_data = new HostData;
	_data->ip = ip;
	_data->port = port;
	_data->serverName = serverName;
}

Host::Host(const Host& other) {}

std::string		Host::getIp() const {
	return _data->host;
}

size_t			Host::getPort() const {
	return _data->port;
}

std::string		Host::getHostName() const {
	return _data->serverName;
	// return _hostName;
}

HostData *Host::getData() const{
	return _data;
}

bool operator==(const Host &lhs, const Host &rhs) {
	if (lhs.getIp() != rhs.getIp()
		|| lhs.getPort() != rhs.getPort()
		|| lhs.getHostName() != rhs.getHostName()){
		return false;
	}
	return true;
}
