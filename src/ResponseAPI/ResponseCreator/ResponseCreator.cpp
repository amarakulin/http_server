#include "ResponseCreator.hpp"

ResponseCreator::ResponseCreator() {}

ResponseCreator::~ResponseCreator() {}

Response *ResponseCreator::createResponse(Request *request) {
	std::string requestMethod = request->getMethod();

	for (int i = 0; responseCreatorList[i].createResponse; i++) {
		if (requestMethod == responseCreatorList[i].method)
			return responseCreatorList[i].createResponse(request);
	}
	
	return new ResponseGet;
}

Response*	createResponseGet(Request* request) {
	std::cout << "GET" << std::endl;
	return new ResponseGet;
}

Response*	createResponsePost(Request* request) {
	std::cout << "POST" << std::endl;
	return new ResponsePost;
}

Response* createResponseDelete(Request* request) {
	std::cout << "DELETE" << std::endl;
	return new ResponseDelete;
}

