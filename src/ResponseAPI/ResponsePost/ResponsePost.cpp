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
	ResponsePost::createBody(requestData, hostData);
	_leftBytesToSend = _dataToSend.length();//TODO set in one place
}

ResponsePost::~ResponsePost() {}


void ResponsePost::createBody(RequestData &requestData, HostData *hostData){
	std::string filePath = getFilePathFromHostData(requestData.header["uri"], hostData);
	if (isFileInPath(filePath)){
		//todo image some filename
	}
	std::ofstream outfile (filePath);
	outfile << requestData.body << std::endl;
	outfile.close();
//	try{
//	std::string dataFromCGI = getDataFromCGI(uri);
	std::string dataFromCGI = "";
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

void ResponsePost::createBody(const std::string &uri, HostData *hostData){
	Response::createBody(uri, hostData);
}
