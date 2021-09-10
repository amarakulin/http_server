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


#include "HostTypes.hpp"
#include "Response.hpp"
#include "Global.hpp"

class ResponseError : public Response {
public:
	ResponseError();
	ResponseError(const ErrorPage &errorPage, HostData *hostData);//TODO add ErrorPage
	ResponseError(const ResponseError& other);
	ResponseError& operator=(const ResponseError &assign);
	~ResponseError();

private:
	virtual void createBody(const std::string &uri, HostData *hostData);
};


#endif
