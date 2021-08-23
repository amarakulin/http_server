#include "Response.hpp"

Response::Response() {}

Response::Response(const Response& other) {}

Response::Response(const Request* request) {}

Response::~Response() {}

std::string Response::createBody() {
	return "";
}

std::string Response::createHead() {
	return "";
}

/*
** Getters
*/

/*
** Setters
*/
