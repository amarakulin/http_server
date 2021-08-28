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
	Request 	req;
	std::string requestSrt = "GET /favicon.ico HTTP/1.1\r\nHost: 127.0.0.1:8000\r\nConnection: keep-alive\r\nPragma: no-cache\r\nCache-Control: no-cache\r\n\r\n";
	req.addRequestChunk(requestSrt);

	ResponseGet *responseGet = new ResponseGet(&req);
	TEST_CHECK(!responseGet->isDone());
	TEST_CHECK(responseGet->getStatus() == SENDING);
	TEST_CHECK(responseGet->getDataToSend().length() == responseGet->getLeftBytesToSend());

	delete responseGet;
}


TEST_LIST = {
		{ "Constructor ResponseGet ", test_response_get },

		{ nullptr, nullptr }
};
