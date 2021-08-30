#include "ResponseCreator.hpp"

ResponseCreator::ResponseCreator() {}

ResponseCreator::~ResponseCreator() {}

Response *ResponseCreator::createResponse(RequestData& requestData) {
	std::string requestMethod = requestData.header["method"];

	for (int i = 0; responseCreatorList[i].createResponse; i++) {
		if (requestMethod == responseCreatorList[i].method)
			return responseCreatorList[i].createResponse(requestData);
	}
	//TODO think about final return
	return new Response;
}

Response *ResponseCreator::createResponse(int status){
	return new ResponseError(status);
}

Response*	createResponseGet(RequestData& requestData) {
	std::cout << "GET" << std::endl;
	return new ResponseGet(requestData);
}

Response*	createResponsePost(RequestData& requestData) {
	std::cout << "POST" << std::endl;
	return new ResponsePost(requestData);
}

Response* createResponseDelete(RequestData& requestData) {
	std::cout << "DELETE" << std::endl;
	return new ResponseDelete(requestData);
}