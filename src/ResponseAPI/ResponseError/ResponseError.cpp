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

ResponseError::ResponseError(int status) {
	logger.printMessage("[+] ResponseError constructor with status: " + std::to_string(status));
	std::string filename = "./error.html";//TODO delete hardcode, get from ErrorPage
	RequestData requestData;
	requestHeaderStruct headerStruct;

	headerStruct.insert(std::make_pair("access", "text/html"));
	headerStruct.insert(std::make_pair("uri", filename));
	requestData.header = headerStruct;
	requestData.body = "";

	_status = status;//TODO delete hardcode, get from ErrorPage
	createHead(requestData);
	createBody(requestData);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponseError::~ResponseError() {}

void	ResponseError::createBody(RequestData &requestData) {//TODO may be change arg RequestData to std::string
	std::string filename = requestData.header.find("uri")->second;
	filename = filename;
	if (filename == "./"){//TODO needs to know default List<file> if directory is given from config
		filename += "index.html";
	}
	std::string body = getDataFileAsString(filename);
	_dataToSend += "\r\n";
	_dataToSend += body;
}