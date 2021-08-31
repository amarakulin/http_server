/* **************************************************************************** */
/*                                                                      .       */
/*   TestResponseError.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 8/31/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "../../../include/acutest.hpp"
#include "../../../src/ResponseAPI/Response/Response.hpp"
#include "../../../src/ResponseAPI/ResponseError/ResponseError.hpp"
#include <iostream>

void
testResponseErrorBadRequest400(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 400 Bad Request\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorForbidden403(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 403 Forbidden\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorNotFound404(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorMethodNotAllowed405(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 405 Method Not Allowed\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorInternalServerError500(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 500 Internal Server Error\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorNotImplemented501(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 501 Not Implemented\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorBadGateway502(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 502 Bad Gateway\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseErrorHTTPVersionNotSupported505(void){
	std::string filename = "./test_files/error.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	std::string expectedResponseData = "HTTP/1.1 505 HTTP Version Not Supported\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;

	ResponseError *response = new ResponseError();//TODO chanege to object ErrorPage
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}
TEST_LIST = {
//		{ "ResponseError: Bad Request [404]", testResponseErrorBadRequest400 },
//		{ "ResponseError: Forbidden [403]", testResponseErrorForbidden403 },
//		{ "ResponseError: Not Found [404]", testResponseErrorNotFound404 },
//		{ "ResponseError: Method Not Allowed [405]", testResponseErrorMethodNotAllowed405 },
//		{ "ResponseError: Internal Server Error [500]", testResponseErrorInternalServerError500 },
//		{ "ResponseError: Not Implemented [501]", testResponseErrorNotImplemented501 },
//		{ "ResponseError: Bad Gateway [502]", testResponseErrorBadGateway502 },
//		{ "ResponseError: HTTP Version Not Supported [505]", testResponseErrorHTTPVersionNotSupported505 },
		{ nullptr, nullptr }
};
