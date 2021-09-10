#include "ResponseGet.hpp"


ResponseGet::ResponseGet() : Response() {}

ResponseGet::ResponseGet(const ResponseGet& other) : Response(other) {
	operator=(other);
}

ResponseGet &ResponseGet::operator=(const ResponseGet &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponseGet::ResponseGet(RequestData &requestData, HostData *hostData)
		: Response(requestData, hostData)
{
	Response::createBody(requestData.header["uri"], hostData);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponseGet::~ResponseGet() {}

void ResponseGet::createBody(const std::string &uri, HostData *hostData)
{
	Response::createBody(uri, hostData);
}
