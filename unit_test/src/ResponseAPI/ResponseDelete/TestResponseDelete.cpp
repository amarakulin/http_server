/* **************************************************************************** */
/*                                                                      .       */
/*   TestResponseDelete.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 9/5/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */



#include "../../../include/acutest.hpp"
#include "../../../src/ResponseAPI/Response/Response.hpp"
#include "../../../src/ResponseAPI/ResponseDelete/ResponseDelete.hpp"
#include "../../../test_utils/MockHostData.hpp"
#include <iostream>
#include <fstream>



void
testResponseDeleteHTMLFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}


void testResponseDeleteCSSFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/index.css";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.css") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/css,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/css\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseDeleteEmptyFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/index.js";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.js") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: */*\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseDeleteWithFile3MB(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/text_3MB.txt";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/text_3MB.txt") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}


void
testResponseDeleteWithOneTypeFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseDeleteWithSeveralTypesFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseDeleteWithEmptyTypeFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	header.insert(std::pair<std::string, std::string>("accept", ""));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: \r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseDeleteWithoutTypeFile(void){
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	requestHeaderStruct header;
	std::string uri = "/index.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
	delete hostData;
}

void
testResponseDeleteWithNotExistFile(void){
	requestHeaderStruct header;
	HostData *hostData = MockHostData::createDefaultHostDataForDelete();
	std::string uri = "/NotExist.html";
	std::string filename = "." + hostData->root + uri;
	std::string body = "File " + uri + " didn't deleted";

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", uri));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;//TODO not OK!!!
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData, hostData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);
	delete response;
	delete hostData;
}

void
testResponseDeleteWithPicture(void){
	TEST_CHECK(false);
}

TEST_LIST = {
		{ "ResponseDelete with HTML file", testResponseDeleteHTMLFile },
		{ "ResponseDelete with CSS file", testResponseDeleteCSSFile },
		{ "ResponseDelete with EMPTY file", testResponseDeleteEmptyFile },
		{ "ResponseDelete with 3 MB file", testResponseDeleteWithFile3MB },
		{ "ResponseDelete with ONE TYPE FILE file", testResponseDeleteWithOneTypeFile },
		{ "ResponseDelete with SEVERAL TYPE FILE file", testResponseDeleteWithSeveralTypesFile },
		{ "ResponseDelete with EMPTY TYPE FILE file", testResponseDeleteWithEmptyTypeFile },
		{ "ResponseDelete with WITHOUT TYPE FILE file", testResponseDeleteWithoutTypeFile },
		{ "ResponseDelete with NOT EXIST FILE", testResponseDeleteWithNotExistFile },

		{ nullptr, nullptr }
};
