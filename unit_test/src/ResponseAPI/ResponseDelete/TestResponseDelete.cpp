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
#include <iostream>
#include <fstream>



void
testResponseDeleteHTMLFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.html";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}


void testResponseDeleteCSSFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.css";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.css") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/css,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/css\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseDeleteEmptyFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.js";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.js") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: */*\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseDeleteWithFile3MB(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/text_3MB.txt";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./test_files/text_3MB.txt") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}


void
testResponseDeleteWithOneTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.html";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseDeleteWithSeveralTypesFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.html";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseDeleteWithEmptyTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.html";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", ""));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-type: \r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseDeleteWithoutTypeFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/index.html";
	std::string body = "OK";

	std::ofstream outfile (filename);
	outfile << getDataFileAsString("./index.html") << std::endl;
	outfile.close();

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
}

void
testResponseDeleteWithNotExistFile(void){
	requestHeaderStruct header;
	std::string filename = "./test_files/forResponseDelete/NotExist.html";
	std::string body = "File " + filename + " didn't deleted";

	long sizeFile = body.length();
	header.insert(std::pair<std::string, std::string>("uri", filename));
	std::string expectedResponseData = "HTTP/1.1 200 OK\r\nContent-length: " + std::to_string(sizeFile) + "\r\n\r\n" + body;
	RequestData requestData = {.header = header, .body = ""};

	ResponseDelete *response = new ResponseDelete(requestData);
	TEST_CHECK(response->getDataToSend() == expectedResponseData);

	delete response;
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
