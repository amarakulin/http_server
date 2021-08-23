#include "Client.hpp"

Client::Client(int socket) : _clientSocket(socket), _request(new Request), _response(nullptr) {}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request), _response(other._response) {}

Client::~Client() {
	// delete _request; //TODO
	delete _response;
}

void		Client::resetRequest() {
	_request->resetRequest();
}

void Client::resetResponse() {
	if (_response) {
		delete _response;
		_response = nullptr;
	}
}

int Client::sendResponse() { //! клиент не отправляет response!! это делает сервер!! BITCH
	return 0; // TODO realization //TODO pichkasik
}

bool	Client::hasResponse() const {
	if (_response)
		return true;
	return false;
}

bool	Client::hasRequest() const {
	if (_request->getStatus() == READED)
		return true;
	return false;
}

/*
** Getters
*/

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