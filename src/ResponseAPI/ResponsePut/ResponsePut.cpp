/* **************************************************************************** */
/*                                                                      .       */
/*   ResponsePut.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 9/17/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "ResponsePut.hpp"

ResponsePut::ResponsePut() : Response() {}

ResponsePut::ResponsePut(const ResponsePut& other) : Response(other) {
	operator=(other);
}

ResponsePut &ResponsePut::operator=(const ResponsePut &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponsePut::ResponsePut(RequestData &requestData, HostData *hostData)
		: Response(requestData,
				   hostData)
{
	ResponsePut::createBody(requestData, hostData);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponsePut::~ResponsePut() {}

std::pair<std::string, std::string> ResponsePut::parseBody(std::string body){
	size_t filenameOffset;
	std::pair<std::string, std::string> bodyStruct;
	std::string filenameSeporator = FILENAME_SEPORATOR;

	size_t file_end = body.find(filenameSeporator, 0);
	if (file_end != std::string::npos){
		filenameOffset = file_end + filenameSeporator.length();
		bodyStruct.first = body.substr(0, file_end);
		bodyStruct.second = body.substr(filenameOffset, body.length() - filenameOffset);
	}
	else{
		bodyStruct.first = "";
		bodyStruct.second = body;
	}
	return bodyStruct;
}



void ResponsePut::createBody(RequestData &requestData, HostData *hostData){
	std::pair<std::string, std::string> bodyStruct;
	std::string filePath;
	Location *location;

	//TODO create a behavior if file gets from uri
	bodyStruct = parseBody(requestData.body);//TODO may be needs a constuctor with size
	location = getLocationByUri(requestData.header["uri"], hostData->location);
	if (bodyStruct.first.empty()){
		bodyStruct.first = getFileNameFromUri(requestData.header["uri"]);
	}
	filePath = "." + getUploadFilePath(location) + bodyStruct.first;

	std::ofstream outfile (filePath);

	outfile << bodyStruct.second << std::endl;
	outfile.close();
	changeContentLength(0);
	_dataToSend += "\r\n";
}

void ResponsePut::createBody(const std::string &uri, HostData *hostData){
	Response::createBody(uri, hostData);
}
