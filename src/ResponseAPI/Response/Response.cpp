#include "Response.hpp"
#include "../../Types/ResponseTypes.hpp"

Response::Response() {}

Response::Response(const Response& other) {
	_status = NO_RESPONSE;
	_leftDataToSend = -1;
}

Response::Response(const Request* request) {
	_status = SENDING;
}

Response::~Response() {}

std::string Response::createBody() {
	return "";
}

std::string Response::createHead() {
	return "";
}

const std::string &Response::getDataToSend() const{
	return _dataToSend;
}

bool Response::isDone(){
	return _status == SENDED;
}

void Response::countSendedData(int byteSended){
	if (byteSended < 0 || byteSended > _leftDataToSend){
		std::cout << "DATA SENT is negative!!!" << std::endl;
		_status = SENDED;
		return;
	}
	_leftDataToSend -= byteSended;
	if (_leftDataToSend == 0 && !_dataToSend.empty()){
		_status = SENDED;
	}
	else if (_leftDataToSend == 0 && _dataToSend.empty()){//TODO delete
		std::cout << "EMPTY SEND!!!" << std::endl;
		return;
	}
	else if (_leftDataToSend < 0){//TODO delete
		std::cout << "1)LEFT DATA SENT error!!!" << std::endl;
		return;
	}
	else if (_leftDataToSend != 0 && _dataToSend.empty()){//TODO delete
		std::cout << "2)LEFT DATA SENT error!!!" << std::endl;
		return;
	}
	_dataToSend.erase(_dataToSend.begin(), _dataToSend.begin() + byteSended);
}

/*
** Getters
*/

/*
** Setters
*/
