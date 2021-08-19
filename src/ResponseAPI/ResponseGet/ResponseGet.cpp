#include "ResponseGet.hpp"

ResponseGet::ResponseGet() : Response() {}

ResponseGet::ResponseGet(const ResponseGet& other) : Response(other) {}

ResponseGet::~ResponseGet() {}

std::string	ResponseGet::createBody() {
	return "";
}