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
	requestHeaderStruct headerStruct;

	headerStruct.insert(std::make_pair("accept", "text/html"));
	headerStruct.insert(std::make_pair("uri", errorPage.errorPagePath));
	requestData.header = headerStruct;
	requestData.body = "";

	_status = static_cast<int> (errorPage.errorNbr);//TODO delete hardcode, get from ErrorPage
	createHead(requestData);
	Response::createBody(requestData.header.find("uri")->second);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponseError::~ResponseError() {}

void	ResponseError::createBody(const std::string& uri) {
	Response::createBody(uri);
}