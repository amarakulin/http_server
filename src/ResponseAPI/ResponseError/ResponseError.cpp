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
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
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
		Location *location = new Location();
		location->root = "/";
		location->way = errorPagePath;
		hostData->location.push_back(location);
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
