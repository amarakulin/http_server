#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request), _response(nullptr) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request){
//	_request = other.getRequest()->clone();
}

Client::~Client() {
//	delete _request;
}

void		Client::resetRequest() {
	_request->resetRequest();
}

Request* Client::getRequest() const{
	return _request;
}

int			Client::getRequestStatus() const {
	return _request->getStatus();
}

int	Client::getSocket() const {
	return _clientSocket;
}


