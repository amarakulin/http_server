#include "ResponseGet.hpp"

ResponseGet::ResponseGet() : Response() {}

ResponseGet::ResponseGet(const ResponseGet& other) : Response(other) {}

ResponseGet::ResponseGet(const Request* request) : Response(request) {


}

ResponseGet::~ResponseGet() {}

std::string ResponseGet::createBody() {
	return "";
}

std::string ResponseGet::createHead(){
	return "";
}

int ResponseGet::send(){
	return 0;
}
