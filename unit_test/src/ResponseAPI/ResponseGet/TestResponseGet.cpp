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
testResponseGetHTMLFileInRootLocation(void)
{
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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

void testResponseGetCSSFileInRootLocation(void)
{
	requestHeaderStruct header;
	std::string filename = "./index.css";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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
testResponseGetEmptyFileInRootLocation(void)
{
	requestHeaderStruct header;
	std::string filename = "./index.js";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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

void
testResponseGetWithFile3MB(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/text_3MB.txt";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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

void
testResponseGetWithRootLocation(void){
	requestHeaderStruct header;
	std::string filename = "./";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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


void
testResponseGetWithFileInNestedLocation_1(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/testIndex.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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

void
testResponseGetWithFileInNestedLocation_2(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/nestedDir/testNestesdIndex.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
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

void
testResponseGetWithOneTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\nContent-type: text/html\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

void
testResponseGetWithSeveralTypesFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\nContent-type: text/html\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

void
testResponseGetWithEmptyTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", ""));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\nContent-type: \r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

void
testResponseGetWithoutTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString('.' + filename);
	long sizeFile = getSizeFile('.' + filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);

	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete request;
}

void
testResponseGetWithPicture(void){
	TEST_CHECK(false);
}

TEST_LIST = {
		{ "ResponseGet with HTML file", testResponseGetHTMLFileInRootLocation },
		{ "ResponseGet with CSS file", testResponseGetCSSFileInRootLocation },
		{ "ResponseGet with EMPTY file", testResponseGetEmptyFileInRootLocation },

		{ "ResponseGet with 3 MB file", testResponseGetWithFile3MB },
		{ "ResponseGet with ROOT LOCATION file", testResponseGetWithRootLocation },
		{ "ResponseGet with NESTED LOCATION 1 file", testResponseGetWithFileInNestedLocation_1 },
		{ "ResponseGet with NESTED LOCATION 2 file", testResponseGetWithFileInNestedLocation_2 },
		{ "ResponseGet with ONE TYPE FILE file", testResponseGetWithOneTypeFile },
		{ "ResponseGet with SEVERAL TYPE FILE file", testResponseGetWithSeveralTypesFile },
		{ "ResponseGet with EMPTY TYPE FILE file", testResponseGetWithEmptyTypeFile },
		{ "ResponseGet with WITHOUT TYPE FILE file", testResponseGetWithoutTypeFile },


		{ nullptr, nullptr }
};
