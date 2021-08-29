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
	header.insert(std::pair<std::string, std::string>("location", "/index.html"));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\n\r\n<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title><link rel=\"stylesheet\" href=\"index.css\"></head><body><h2>Hello</h2><script src=\"index.js\"></script></body></html>";
	RequestData requestData = {
		.header = header, .body = ""};
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
	header.insert(std::pair<std::string, std::string>("location", "/index.css"));
	header.insert(std::pair<std::string, std::string>("accept", "text/css,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: 68\r\nContent-type: text/css\r\n\r\nbody{background-color: lightblue;}h1{color: navy;margin-left: 20px;}";
	RequestData requestData = {
			.header = header, .body = ""};
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
	header.insert(std::pair<std::string, std::string>("location", "/index.js"));
	header.insert(std::pair<std::string, std::string>("accept", "*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: 0\r\nContent-type: */*\r\n\r\n";
	RequestData requestData = {
			.header = header, .body = ""};
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
