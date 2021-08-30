/* **************************************************************************** */
/*                                                                      .       */
/*   ResponseError.hpp                                                        / V\     */
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


#ifndef RESPONSE_Error
# define RESPONSE_Error


#include "Response.hpp"
#include "Global.hpp"

class ResponseError : public Response {
public:
	ResponseError();
	ResponseError(int status);//TODO add ErrorPage
	ResponseError(const ResponseError& other);
	~ResponseError();

	void createBody(RequestData &requestData);
};


#endif
