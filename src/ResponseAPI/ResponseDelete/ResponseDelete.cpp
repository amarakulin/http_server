#include "ResponseDelete.hpp"

ResponseDelete::ResponseDelete() : Response() {}

ResponseDelete::ResponseDelete(const ResponseDelete& other) : Response(other) {}

ResponseDelete::ResponseDelete(RequestData& requestData) : Response(requestData) {}

ResponseDelete::~ResponseDelete() {}

void ResponseDelete::createBody(const std::string &uri){
	Response::createBody(uri);
}
