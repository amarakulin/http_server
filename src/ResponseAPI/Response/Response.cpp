#include "Response.hpp"
#include "../../Types/ResponseTypes.hpp"

Response::Response() {
	_status = NO_RESPONSE;
	_leftDataToSend = 0;//TODO Think
}

Response::Response(const Response& other) {
}

Response::Response(const Request* request) {
	_status = SENDING;
}

Response::~Response() {}

const std::string &Response::getDataToSend() const{
	return _dataToSend;
}

bool Response::isDone(){
	return _status == SENDED;
}

void Response::countSendedData(int byteSended){
	std::cout << "BEFORE leftDataToSend: " << _leftDataToSend << std::endl;
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
	std::cout << "dataToSend: " << _dataToSend << std::endl;
	std::cout << "AFTER leftDataToSend: " << _leftDataToSend << std::endl;

}

size_t Response::getLeftDataToSend() const {
	return _leftDataToSend;
}

int Response::getStatus() const {
	return _status;
}

/*
** Getters
*/

/*
** Setters
*/
