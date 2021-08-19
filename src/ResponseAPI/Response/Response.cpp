#include "Response.hpp"

Response::Response() : _status(NO_RESPONSE) {}

Response::~Response() {}

std::string Response::createBody() {
	return "";
}

std::string Response::createHead() {
	return "";
}

bool Response::isResponseSended(){
	return false;//TODO realization
}
