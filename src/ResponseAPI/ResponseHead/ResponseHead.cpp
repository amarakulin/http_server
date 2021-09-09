/* **************************************************************************** */
/*                                                                      .       */
/*   ResponseHead.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 9/5/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "ResponseHead.hpp"

ResponseHead::ResponseHead() : Response() {}

ResponseHead::ResponseHead(const ResponseHead& other) : Response(other) {
	operator=(other);
}

ResponseHead &ResponseHead::operator=(const ResponseHead &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponseHead::ResponseHead(RequestData &requestData, HostData *hostData)
		: Response(requestData,
				   NULL)
{
	ResponseHead::createBody(requestData.header["uri"]);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponseHead::~ResponseHead() {}

void ResponseHead::createBody(const std::string& uri) {
	_dataToSend += "\r\n";
}
