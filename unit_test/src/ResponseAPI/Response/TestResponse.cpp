/* **************************************************************************** */
/*                                                                      .       */
/*   TestResponse.cpp                                                        / V\     */
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

void testResponseIsDoneWhenStatusSended(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	RequestData requestData = {.header = header, .body = ""};
	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	response->countSendedData(response->getDataToSend().length());

	TEST_CHECK(response->isDone());

	delete response;
	delete hostData;
}

void testResponseIsDoneWhenStatusNoResponse(void){
	Response response;
	TEST_CHECK(!response.isDone());
}

void testResponseIsDoneWhenStatusSening(void){
	requestHeaderStruct header;
	std::string filename = "./index.html";
	header.insert(std::pair<std::string, std::string>("uri", filename));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));
	RequestData requestData = {.header = header, .body = ""};

	HostData *hostData = MockHostData::createDefaultHostData();
	ResponseGet *response = new ResponseGet(requestData, hostData);
	response->countSendedData(response->getDataToSend().length() / 2);

	TEST_CHECK(!response->isDone());

	delete response;
	delete hostData;
}

TEST_LIST = {
		{ "isDone -> SENDED", testResponseIsDoneWhenStatusSended },
		{ "isDone -> NO_RESPONSE", testResponseIsDoneWhenStatusNoResponse },
		{ "isDone -> SENDING", testResponseIsDoneWhenStatusSening },
		{ nullptr, nullptr }
};

