#include "Config.hpp"

Config::Config() : _hosts() {}

Config::Config(const Config& other) : _hosts(other._hosts) {}

Config::~Config() {
	std::vector<Host*>::iterator it = _hosts.begin();
	for (; it != _hosts.end(); it++) {
		// std::cout << "delete host in config" << std::endl;
		delete *it;
	}
}

void	Config::addNewHost(Host* host) {
	_hosts.push_back(host);
}

/*
** Getters
*/

std::vector<Host*>	Config::getHosts() const {
	return _hosts;
}