#include "Server.hpp"

Server::Server() {

}

Server::Server(const Config* config) : _config(config), _hosts(config->getHosts()){}

Server::~Server() {
	delete _config;
}

void	Server::start() {

}