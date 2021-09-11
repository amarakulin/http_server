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
		: Response(requestData, NULL)
{
	Response::createBody(requestData.header["uri"]);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponseGet::~ResponseGet() {}

void ResponseGet::createBody(const std::string& uri) {
	Response::createBody(uri);
}
