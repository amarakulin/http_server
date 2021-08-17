#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request() {}

Client::Client(const Client& other) {
	*this = other;
}

Client::~Client() {}

Request& Client::getRequest() {
	return _request;
}

int	Client::getSocket() const {
	return _clientSocket;
}