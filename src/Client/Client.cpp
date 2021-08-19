#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request), _response(new Response) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request), _response(other._response) {}

Client::~Client() {
	// delete _request; //TODO
	// delete _response;
}

void		Client::resetRequest() {
	_request->resetRequest();
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

int Client::sendResponse() { //! клиент не отправляет response!! это делает сервер!! BITCH
	return 0; // TODO realization //TODO pichkasik
}

/*
** Getters
*/

int			Client::getResponseStatus() const {
	return _response->getStatus();
}

int			Client::getRequestStatus() const {
	return _request->getStatus();
}

Request* 	Client::getRequest() const{
	return _request;
}

Response*	Client::getResponse() const {
	return _response;
}

int			Client::getSocket() const {
	return _clientSocket;
}

/*
** Setters
*/

void Client::setResponse(Response *response) {
	resetResponse();
	_response = response;
}