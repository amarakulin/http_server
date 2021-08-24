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
#include "../../../src/Request/Request.hpp"
#include "../../../../src/ResponseAPI/ResponseCreator/ResponseCreator.hpp"
#include "../../../src/Types/ResponseTypes.hpp"
#include <iostream>

void testResponseIsDoneWhenStatusSended(void){
	TEST_CHECK(false);
}

void testResponseIsDoneWhenStatusNoResponse(void){
	Response response;
	TEST_CHECK(!response.isDone());
}

void testResponseIsDoneWhenStatusSening(void){
	TEST_CHECK(false);

}

TEST_LIST = {
		{ "isDone -> SENDED", testResponseIsDoneWhenStatusSended },
		{ "isDone -> NO_RESPONSE", testResponseIsDoneWhenStatusNoResponse },
		{ "isDone -> SENDING", testResponseIsDoneWhenStatusSening },
		{ nullptr, nullptr }
};

