#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request), _response(new Response) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request){}

Client::~Client() {
	// delete _request; //TODO
	// delete _response;
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

void Client::setResponse(Response *response) {
	resetResponse();
	_response = response;
}

void Client::resetResponse() {
	delete _response;
}

bool Client::isResponseSended() {
	return _response->isResponseSended();
}

bool Client::isResponseEmpty() {
	return _response == nullptr;
}

int Client::sendResponse() {
	return 0; // TODO realization //TODO pichkasik
}

int	Client::getResponseStatus() const {
	return _response->getStatus();
}


