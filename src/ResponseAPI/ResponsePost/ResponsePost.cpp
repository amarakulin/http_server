#include "ResponsePost.hpp"

ResponsePost::ResponsePost() : Response() {}

ResponsePost::ResponsePost(const ResponsePost& other) : Response(other) {
	operator=(other);
}

ResponsePost &ResponsePost::operator=(const ResponsePost &assign) {
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getState();
		_status = assign.getStatus();
	}
	return *this;
}

ResponsePost::ResponsePost(RequestData &requestData, HostData *hostData)
		: Response(requestData,
				   NULL)
{
	ResponsePost::createBody(requestData.header["uri"]);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponsePost::~ResponsePost() {}

void ResponsePost::createBody(const std::string& uri) {
	std::string dataFromCGI = getDataFromCGI(uri);
	changeContentLength(dataFromCGI.length());
	_dataToSend += "\r\n";
	_dataToSend += dataFromCGI;
}

std::string ResponsePost::getDataFromCGI(const std::string &uri){
	return "Here should be CGI";
}
