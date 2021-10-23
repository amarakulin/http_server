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
				   hostData)
{
	ResponseHead::createBody(requestData.header["uri"], hostData);
	_leftBytesToSend = _dataToSend.length();
}

ResponseHead::~ResponseHead() {}

void ResponseHead::createBody(const std::string &uri, HostData *hostData)
{
	_dataToSend += "\r\n";
}
