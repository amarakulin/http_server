#include "Client.hpp"

Client::Client(int socket, HostData *hostData)
		: _clientSocket(socket), _request(new Request), _response(nullptr), _hostData(hostData) {
}

Client::Client(const Client& other) : _clientSocket(other._clientSocket), _request(other._request), _response(other._response), _hostData(other._hostData) {}

Client::~Client() {
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

HostData *Client::getHostData() const{
	return _hostData;
}
