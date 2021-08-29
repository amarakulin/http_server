#include "ResponseCreator.hpp"

ResponseCreator::ResponseCreator() {}

ResponseCreator::~ResponseCreator() {}

Response *ResponseCreator::createResponse(Request *request) {
	std::string requestMethod = request->getMethod();

	for (int i = 0; responseCreatorList[i].createResponse; i++) {
		if (requestMethod == responseCreatorList[i].method)
			return responseCreatorList[i].createResponse(request);
	}
	//TODO think about final return
	return new Response;
}

Response*	createResponseGet(Request* request) {
	std::cout << "GET" << std::endl;
	return new ResponseGet(request);
}

Response*	createResponsePost(Request* request) {
	std::cout << "POST" << std::endl;
	return new ResponsePost(request);
}

Response* createResponseDelete(Request* request) {
	std::cout << "DELETE" << std::endl;
	return new ResponseDelete(request);
}

Response* createResponseError(Request* request) {
	std::cout << "ERROR" << std::endl;
	return new ResponseError(request);
}