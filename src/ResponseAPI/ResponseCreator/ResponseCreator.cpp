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

Response *ResponseCreator::createResponse(const ErrorPage &errorPage){
	logger.printMessage("[+] ResponseError with status code: " + std::to_string(errorPage.errorNbr));
	return new ResponseError(errorPage);
}

Response*	createResponseGet(RequestData& requestData) {
	logger.printMessage("[+] ResponseGet");
	return new ResponseGet(requestData);
}

Response*	createResponsePost(RequestData& requestData) {
	logger.printMessage("[+] ResponsePost");
	return new ResponsePost(requestData);
}

Response*	createResponseHead(RequestData& requestData) {
	logger.printMessage("[+] ResponseHead");
	return new ResponseHead(requestData);
}

Response* createResponseDelete(RequestData& requestData) {
	logger.printMessage("[+] ResponseDelete");
	return new ResponseDelete(requestData);
}