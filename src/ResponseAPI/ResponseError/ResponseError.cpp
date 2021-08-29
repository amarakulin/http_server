/* **************************************************************************** */
/*                                                                      .       */
/*   ResponseError.cpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 8/29/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#include "ResponseError.hpp"

ResponseError::ResponseError() : Response() {}

ResponseError::ResponseError(const ResponseError& other) : Response(other) {}

ResponseError::ResponseError(Request* request) : Response(request) {}

ResponseError::~ResponseError() {}

std::string	ResponseError::createBody() {
	return "";
}