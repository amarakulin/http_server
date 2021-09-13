#include "ResponsePost.hpp"
#include "ResponseError.hpp"

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
				   hostData)
{
	ResponsePost::createBody(requestData.header["uri"], hostData);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponsePost::~ResponsePost() {}

void ResponsePost::createBody(const std::string &uri, HostData *hostData)
{
//	try{
		std::string dataFromCGI = getDataFromCGI(uri);
		changeContentLength(dataFromCGI.length());
		_dataToSend += "\r\n";
		_dataToSend += dataFromCGI;
//	}
//	catch (InternalServerErrorException e){
//		ResponseError responseError(getErrorPageStruct(INTERNAL_SERVER_ERROR, hostData->errorPage), hostData);
//		_dataToSend = responseError.getDataToSend();
//	}
//	catch (BadGatewayException e){
//		ResponseError responseError(getErrorPageStruct(BAD_GATE_WAY, hostData->errorPage), hostData);
//		_dataToSend = responseError.getDataToSend();
//	}
}

std::string ResponsePost::getDataFromCGI(const std::string &uri){
	return "Here should be CGI";
}
