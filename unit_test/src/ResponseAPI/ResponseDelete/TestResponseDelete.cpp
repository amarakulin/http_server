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
testResponseDeleteHTMLFileInRootLocation(void){
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


TEST_LIST = {
		{ "ResponseDelete with HTML file", testResponseDeleteHTMLFileInRootLocation },

		{ nullptr, nullptr }
};
