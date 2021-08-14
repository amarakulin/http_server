#include "Host.hpp"

Host::Host() {}

Host::Host(std::string ip, size_t port, std::string hostName)
	: _ip(ip), _port(port), _hostName(hostName) {}

std::string 	Host::getIp() const {
	return _ip;
}

size_t			Host::getPort() const {
	return _port;
}

std::string		Host::getHostName() const {
	return _hostName;
}
