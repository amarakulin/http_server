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
testResponseGetHTMLFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void testResponseGetCSSFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.css";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/css,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/css\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetEmptyFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.js";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: */*\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithFile3MB(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/text_3MB.txt";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithRootLocation(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRoot();
	std::string uri = "/";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename + "root_file.html");
	long sizeFile = getSizeFile(filename + "root_file.html");
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}


void
testResponseGetWithFileInNestedLocation(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataNestedDir();
	std::string uri = "/test_files/nestedDir";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithOneTypeFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithSeveralTypesFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithEmptyTypeFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", ""));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: \r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseGet *response = new ResponseGet(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseGetWithoutTypeFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataRootTestFiles();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = getDataFileAsString(filename);
	long sizeFile = getSizeFile(filename);
	header.insert(std::pair<std::string, std::string>("uri", uri));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

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
		{ "ResponseGet with HTML file", testResponseGetHTMLFile },
		{ "ResponseGet with CSS file", testResponseGetCSSFile },
		{ "ResponseGet with EMPTY file", testResponseGetEmptyFile },

		{ "ResponseGet with 3 MB file", testResponseGetWithFile3MB },
		{ "ResponseGet with ROOT LOCATION file", testResponseGetWithRootLocation },
		{ "ResponseGet with NESTED LOCATION file", testResponseGetWithFileInNestedLocation },
		{ "ResponseGet with ONE TYPE FILE file", testResponseGetWithOneTypeFile },
		{ "ResponseGet with SEVERAL TYPE FILE file", testResponseGetWithSeveralTypesFile },
		{ "ResponseGet with EMPTY TYPE FILE file", testResponseGetWithEmptyTypeFile },
		{ "ResponseGet with WITHOUT TYPE FILE file", testResponseGetWithoutTypeFile },


		{ nullptr, nullptr }
};
