#include "ResponseDelete.hpp"


ResponseDelete::ResponseDelete() : Response() {}

ResponseDelete::ResponseDelete(const ResponseDelete& other) : Response(other) {
	operator=(other);
}

ResponseDelete &ResponseDelete::operator=(const ResponseDelete &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponseDelete::ResponseDelete(RequestData &requestData, HostData *hostData)
		: Response(requestData,
				   NULL)
{
	ResponseDelete::createBody(requestData.header["uri"]);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponseDelete::~ResponseDelete() {}

void ResponseDelete::createBody(const std::string& uri) {
	std::string body = "";

	if (!std::remove(uri.c_str())){
		body += "OK";
	}
	else{
		body += "File " + uri + " didn't deleted";
	}
	changeContentLength(body.length());

	_dataToSend += "\r\n";
	_dataToSend += body;
}
