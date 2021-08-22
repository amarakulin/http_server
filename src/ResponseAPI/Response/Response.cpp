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

int Response::send(){
	return 0;
}

/*
** Getters
*/

/*
** Setters
*/
