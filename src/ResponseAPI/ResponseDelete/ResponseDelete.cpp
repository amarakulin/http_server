#include "ResponseDelete.hpp"

ResponseDelete::ResponseDelete() : Response() {}

ResponseDelete::ResponseDelete(const ResponseDelete& other) : Response(other) {}

ResponseDelete::ResponseDelete(const Request* request) : Response(request) {}

ResponseDelete::~ResponseDelete() {}

std::string	ResponseDelete::createBody() {
	return "";
}