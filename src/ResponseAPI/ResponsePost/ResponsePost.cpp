#include "ResponsePost.hpp"

ResponsePost::ResponsePost() : Response() {}

ResponsePost::ResponsePost(const ResponsePost& other) : Response(other) {}

ResponsePost::ResponsePost(const Request* request) : Response(request) {}

ResponsePost::~ResponsePost() {}

std::string	ResponsePost::createBody() {
	return "";
}