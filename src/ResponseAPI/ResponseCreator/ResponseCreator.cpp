#include "ResponseCreator.hpp"

ResponseCreator::ResponseCreator() {}

ResponseCreator::~ResponseCreator() {}

Response *ResponseCreator::createResponse(RequestData &requestData,
										  HostData *hostData)
{
	std::string requestMethod = requestData.header["method"];

	for (int i = 0; responseCreatorList[i].createResponse; i++) {
		if (requestMethod == responseCreatorList[i].method)
			return responseCreatorList[i].createResponse(requestData, hostData);
	}
	//TODO think about final return
	return new Response;
}

Response *ResponseCreator::createResponse(const ErrorPage &errorPage){
	logger.printMessage("[+] ResponseError with status code: " + std::to_string(errorPage.errorNbr));
	return new ResponseError(errorPage, NULL);
}

Response *createResponseGet(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponseGet");
	return new ResponseGet(requestData, NULL);
}

Response *createResponsePost(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponsePost");
	return new ResponsePost(requestData, NULL);
}

Response *createResponseHead(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponseHead");
	return new ResponseHead(requestData, NULL);
}

Response *createResponseDelete(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponseDelete");
	return new ResponseDelete(requestData, NULL);
}