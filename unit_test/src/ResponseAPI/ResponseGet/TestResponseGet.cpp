/* **************************************************************************** */
/*                                                                      .       */
/*   TestResponseGet.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 8/24/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */

#include "../../../include/acutest.hpp"
#include "../../../src/ResponseAPI/Response/Response.hpp"
#include "../../../src/ResponseAPI/ResponseGet/ResponseGet.hpp"
#include "../../../src/Request/Request.hpp"
#include "../../../../src/ResponseAPI/ResponseCreator/ResponseCreator.hpp"
#include "../../../src/Types/ResponseTypes.hpp"
#include <iostream>

void
testResponseGetHTMLFile(void)
{
	requestHeaderStruct header;
	std::string filename = "/index.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("location", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\nContent-type: text/html\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

void testResponseGetCSSFile(void)
{
	requestHeaderStruct header;
	std::string filename = "/index.css";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("location", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/css,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\nContent-type: text/css\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

void
testResponseGetEmptyFile(void)
{
	requestHeaderStruct header;
	std::string filename = "/index.js";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("location", filename));
	header.insert(std::pair<std::string, std::string>("accept", "*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\nContent-type: */*\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

TEST_LIST = {
		{ "Constructor ResponseGet with HTML file", testResponseGetHTMLFile },
		{ "Constructor ResponseGet with CSS file", testResponseGetCSSFile },
		{ "Constructor ResponseGet with EMPTY file", testResponseGetEmptyFile },


		{ nullptr, nullptr }
};
