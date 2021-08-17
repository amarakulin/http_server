#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request) {
	// _request = new Request;
	// _request->_data = other.getRequest()->getData();
}

Client::~Client() {
	// delete _request;
}

Request* Client::getRequest() {
	return _request;
}

// Request* Client::getRequest() const {
// 	return _request;
// }

int	Client::getSocket() const {
	return _clientSocket;
}