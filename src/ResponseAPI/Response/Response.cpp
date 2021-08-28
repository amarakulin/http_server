#include "Response.hpp"
#include "../../Types/ResponseTypes.hpp"

Response::Response() {
	_state = NO_RESPONSE;
	_leftBytesToSend = 0;//TODO Think
}

Response::Response(const Response& other) {
	operator=(other);
}

Response::Response(const Request* request) {
	_state = SENDING;
}

Response &Response::operator=(const Response &assign){
	if (this != &assign){
		_leftBytesToSend = assign.getLeftBytesToSend();
		_dataToSend = assign.getDataToSend();
		_state = assign.getStatus();
	}
	return *this;
}

Response::~Response() {}



bool Response::isDone(){
	return _state == SENDED;
}

void Response::countSendedData(int byteSended){
	if (byteSended < 0 || byteSended > _leftBytesToSend){
		std::cout << "DATA SENT is negative!!!" << std::endl;
	}
	_leftBytesToSend -= byteSended;
	if (_leftBytesToSend == 0 && !_dataToSend.empty()){
		_state = SENDED;
	}
	_dataToSend.erase(_dataToSend.begin(), _dataToSend.begin() + byteSended);
}


/*
** Getters
*/

size_t Response::getLeftBytesToSend() const {
	return _leftBytesToSend;
}

const std::string &Response::getDataToSend() const{
	return _dataToSend;
}

int Response::getStatus() const {
	return _state;
}

void Response::createHead(){

}

/*
** Setters
*/
