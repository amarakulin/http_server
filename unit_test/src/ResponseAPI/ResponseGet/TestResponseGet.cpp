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
test_response_get(void)
{
	requestHeaderStruct header;
	header.insert(std::pair<std::string, std::string>("location", "/index.html"));
	header.insert(std::pair<std::string, std::string>("accept", "text/html,*/*"));

	RequestData requestData = {
		.header = header, .body = "",
	};
	Request *request = new Request();
	request->setData(requestData);
	ResponseGet *response = new ResponseGet(request);
	TEST_CHECK(!response->isDone());

	delete response;
	delete request;
}


TEST_LIST = {
		{ "Constructor ResponseGet ", test_response_get },

		{ nullptr, nullptr }
};
