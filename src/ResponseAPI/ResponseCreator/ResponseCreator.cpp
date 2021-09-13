#include <Host.hpp>
#include "ResponseCreator.hpp"

ResponseCreator::ResponseCreator() {}

ResponseCreator::~ResponseCreator() {}

Response *ResponseCreator::createResponse(RequestData &requestData,
										  HostData *hostData)
{
	std::string requestMethod = requestData.header["method"];
	int statusCode = ResponseError::isResponseError(requestData, hostData);

	if (statusCode != STATUS_OK){
		return createResponse(ResponseError::getErrorPageStruct(statusCode, hostData->errorPage), hostData);
	}
	for (int i = 0; responseCreatorList[i].createResponse; i++) {
		if (requestMethod == responseCreatorList[i].method)
			return responseCreatorList[i].createResponse(requestData, hostData);
	}
	return createResponse(ResponseError::getErrorPageStruct(INTERNAL_SERVER_ERROR, hostData->errorPage), hostData);
}

Response *ResponseCreator::createResponse(const ErrorPage &errorPage, HostData *hostData)
{
	logger.printMessage("[+] ResponseError with status code: " + std::to_string(errorPage.errorNbr));
	return new ResponseError(errorPage, hostData);
}

Response *createResponseGet(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponseGet");
	return new ResponseGet(requestData, hostData);
}

Response *createResponsePost(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponsePost");
	return new ResponsePost(requestData, hostData);
}

Response *createResponseHead(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponseHead");
	return new ResponseHead(requestData, hostData);
}

Response *createResponseDelete(RequestData &requestData, HostData *hostData)
{
	logger.printMessage("[+] ResponseDelete");
	return new ResponseDelete(requestData, hostData);
}