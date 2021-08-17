#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request) {
//	_request = other.getRequest()->clone();
}

Client::~Client() {
//	delete _request;
}

Request* Client::getRequest() const{
	return _request;
}

// Request* Client::getRequest() const {
// 	return _request;
// }

int	Client::getSocket() const {
	return _clientSocket;
}

