#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request), _response(nullptr) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request){
//	_request = other.getRequest()->clone();
}

Client::~Client() {
	if (_request != nullptr){
		delete _request;
	}
	if (_response != nullptr){
		delete _response;
	}
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

void Client::setResponse(Response *response){
	if (_response != nullptr){
		delete _response;
	}
	_response = response;
}


