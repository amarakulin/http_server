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
#include "../../../test_utils/MockHostData.hpp"
#include <iostream>

void
testResponseGetHTMLFileInRootLocation(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void testResponseGetCSSFileInRootLocation(void){
	requestHeaderStruct header;
	std::string filename = "./index.css";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/css,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/css\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetEmptyFileInRootLocation(void){
	requestHeaderStruct header;
	std::string filename = "./index.js";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: */*\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithFile3MB(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/text_3MB.txt";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithRootLocation(void){
	requestHeaderStruct header;
	std::string filename = "./";
	std::string body = getDataFileAsString(filename + "index.html");//TODO Search for default file
	long sizeFile = getSizeFile(filename + "index.html");//TODO Search for default file
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}


void
testResponseGetWithFileInNestedLocation_1(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/testIndex.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithFileInNestedLocation_2(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/nestedDir/testNestesdIndex.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithOneTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithSeveralTypesFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithEmptyTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", ""));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: \r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithoutTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", filename));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
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
