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
	if (requestMethod == "get")
		return createResponseGet(request);
	else if (requestMethod == "post")
		return createResponsePost(request);
	else if (requestMethod == "delete")
		return createResponseDelete(request);
	//TODO change final return
	return new ResponseGet(request);
}
