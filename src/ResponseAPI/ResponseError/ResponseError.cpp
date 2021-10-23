/* **************************************************************************** */
/*                                                                      .       */
/*   ResponseError.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 8/29/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "ResponseError.hpp"

ResponseError::ResponseError() : Response() {}

ResponseError::ResponseError(const ResponseError& other) : Response(other) {
	operator=(other);
}

ResponseError &ResponseError::operator=(const ResponseError &assign){
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponseError::ResponseError(const ErrorPage &errorPage, HostData *hostData)
{
	logger.printMessage("[+] ResponseError constructor with status: " + std::to_string(errorPage.errorNbr));
	RequestData requestData;

	requestData = fillRequestData(errorPage, hostData);
	_status = static_cast<int> (errorPage.errorNbr);
	createHead(requestData, hostData);
	Response::createBody(requestData.header.find("uri")->second, hostData);
	_leftBytesToSend = _dataToSend.length();
}

ResponseError::~ResponseError() {}

void ResponseError::createBody(const std::string &uri, HostData *hostData){
	Response::createBody(uri, hostData);
}

RequestData
ResponseError::fillRequestData(const ErrorPage &errorPage, HostData *hostData)
{
	RequestData requestData;
	requestHeaderStruct headerStruct;
	std::string errorPagePath = "";
	if (isFileExist("." + hostData->root +  errorPage.errorPagePath) && !errorPage.errorPagePath.empty()){
		errorPagePath = errorPage.errorPagePath;
	}
	else{
		errorPagePath = getErrorPageFromResources(errorPage.errorNbr);
	}

	headerStruct.insert(std::make_pair("accept", "text/html"));
	headerStruct.insert(std::make_pair("uri", errorPagePath));
	requestData.header = headerStruct;
	requestData.body = "";
	return requestData;
}

std::string ResponseError::getErrorPageFromResources(size_t statusCode){
	std::string errorPagePath = DEFAULT_ERROR_PAGE_PATH + std::to_string(statusCode) + ".html";
	if (!isFileExist("." + errorPagePath)){
		errorPagePath = DEFAULT_ERROR_PAGE_PATH + std::to_string(INTERNAL_SERVER_ERROR) + ".html";
	}
	return errorPagePath;
}

int ResponseError::isResponseError(RequestData &requestData, HostData *hostData){
	int statusCode = STATUS_OK;
	std::string filePath = getFilePathFromHostData(requestData.header["uri"], hostData);
	Location *location = getLocationByUri(requestData.header["uri"], hostData->location);
	bool isBodySizeTooLarge = location
								&& ((location->clientMaxBodySize != 0 && requestData.body.size() > location->clientMaxBodySize)
								|| (requestData.body.size() > hostData->clientMaxBodySize));

	logger.printMessage("Uri: " + requestData.header["uri"]);
	logger.printMessage("filePath: " + filePath);

	if (location && location->redirectStatusCode == REDIRECT){
		statusCode = REDIRECT;
	}
	else if (!isFileExist(filePath) && ((requestData.header["method"] != "post") && (requestData.header["method"] != "put"))){
		statusCode = NOT_FOUND;
	}
	else if (isBodySizeTooLarge){
		statusCode = PAYLOAD_TOO_LARGE;
	}
	else if (requestData.header["protocol"] != "http/1.1"){
		statusCode = HTTP_NOT_SUPPORTED;
	}
	else if (location && !isItemInVector(split(PROCESSED_REQUESTS_LOWER, " "), requestData.header["method"])){
		statusCode = NOT_IMPLEMENTED;
	}
	else if (location && !isItemInVector(location->httpMethods, requestData.header["method"])){
		statusCode = METHOD_NOT_ALLOWED;
	}
	return statusCode;
}

ErrorPage ResponseError::getErrorPageStruct(int statusCode, std::vector<ErrorPage*> errorPages){
	ErrorPage errorPage;
	errorPage.errorNbr = statusCode;
	errorPage.errorPagePath = "";
	for (size_t i = 0; i < errorPages.size(); ++i){
		if (errorPages[i]->errorNbr == statusCode){
			errorPage.errorPagePath = errorPages[i]->errorPagePath;
			break;
		}
	}
	return errorPage;
}
