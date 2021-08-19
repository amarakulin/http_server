#include "Response.hpp"

Response::Response() : _status(NO_RESPONSE) {}

Response::Response(const Response& other) : _status(other._status) {}

Response::~Response() {}

std::string Response::createBody() {
	return "";
}

std::string Response::createHead() {
	return "";
}

bool 		Response::isResponseSended() {
	return false;//TODO realization
}

/*
** Getters
*/

int			Response::getStatus() const {
	return _status;
}
