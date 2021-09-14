#include "Config.hpp"

Config::Config() : _hosts() {}

Config::Config(const Config& other) : _hosts(other._hosts) {}

Config::~Config() {
	std::vector<Host*>::iterator it = _hosts.begin();
	for (; it != _hosts.end(); it++) {
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