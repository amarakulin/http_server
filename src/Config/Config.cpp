#include "Config.hpp"

Config::Config() : _hosts() {}

Config::Config(const Config& other) : _hosts(other._hosts) {}

Config::~Config() {}

void	Config::addNewHost(const Host& host) {
	_hosts.push_back(host);
}

/*
** Getters
*/

std::vector<Host>	Config::getHosts() const {
	return _hosts;
}