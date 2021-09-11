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
