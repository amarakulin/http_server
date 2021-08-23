#include "ResponseCreator.hpp"

ResponseCreator::ResponseCreator() {}

ResponseCreator::~ResponseCreator() {}

ResponseGet*	ResponseCreator::createResponseGet(Request* request) {
	return new ResponseGet(request);
}

ResponsePost*	ResponseCreator::createResponsePost(Request* request) {
	return new ResponsePost(request);
}

ResponseDelete* ResponseCreator::createResponseDelete(Request* request) {
	return new ResponseDelete(request);
}

Response *ResponseCreator::createResponse(Request *request) {
	std::string requestMethod = request->getMethod();
	
	if (requestMethod == "GET")
		return createResponseGet(request);
	else if (requestMethod == "POST")
		return createResponsePost(request);
	else if (requestMethod == "DELETE")
		return createResponseDelete(request);
	return new ResponseGet;
}
