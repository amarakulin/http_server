#include "ResponseDelete.hpp"

ResponseDelete::ResponseDelete() : Response() {}

ResponseDelete::ResponseDelete(const ResponseDelete& other) : Response(other) {}

ResponseDelete::~ResponseDelete() {}

std::string	ResponseDelete::createBody() {
	return "";
}