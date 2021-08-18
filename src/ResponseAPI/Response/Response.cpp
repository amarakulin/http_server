#include "Response.hpp"

Response::Response() {}

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
