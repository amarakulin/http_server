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
#include "utils.hpp"

class ResponseError : public Response {

public:
	static int isResponseError(RequestData &requestData, HostData *hostData);
	static ErrorPage getErrorPageStruct(int statusCode, std::vector<ErrorPage*> errorPages);

public:
	ResponseError();
	ResponseError(const ErrorPage &errorPage, HostData *hostData);
	ResponseError(const ResponseError& other);
	ResponseError& operator=(const ResponseError &assign);
	~ResponseError();

private:
	virtual void createBody(const std::string &uri, HostData *hostData);
	RequestData fillRequestData(const ErrorPage &errorPage, HostData *hostData);
	std::string getErrorPageFromResources(size_t statusCode);

};


#endif
