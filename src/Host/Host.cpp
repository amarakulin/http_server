#include "Host.hpp"

Host::Host() {}

Host::Host(std::string ip, size_t port, std::string hostName) {}

Host::Host(const Host& other) {}

std::string		Host::getIp() const {
	return _data.ip;
}

size_t			Host::getPort() const {
	return _data.port;
}

std::string		Host::getHostName() const {
	return _data.host;
	// return _hostName;
}

bool operator==(const Host &lhs, const Host &rhs) {
	if (lhs.getIp() != rhs.getIp()
		|| lhs.getPort() != rhs.getPort()
		|| lhs.getHostName() != rhs.getHostName()){
		return false;
	}
	return true;
}
