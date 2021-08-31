#include "ResponsePost.hpp"

ResponsePost::ResponsePost() : Response() {}

ResponsePost::ResponsePost(const ResponsePost& other) : Response(other) {}

ResponsePost::ResponsePost(RequestData& requestData) : Response(requestData) {}

ResponsePost::~ResponsePost() {}

void ResponsePost::createBody(const std::string &uri){
	Response::createBody(uri);
}