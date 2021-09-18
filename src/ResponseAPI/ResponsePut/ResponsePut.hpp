/* **************************************************************************** */
/*                                                                      .       */
/*   ResponsePut.hpp                                                        / V\     */
/*                                                                   / `  /     */
/*   By: tilda      <tilda@student.21-school.ru.fr>                 <<   |      */
/*                                                                  /    |      */
/*   Created: 9/17/21 by tilda                                    /      |      */
/*                                                              /        |      */
/*                                                            /    \  \ /       */
/*                                                           (      ) | |       */
/*                                                   ________|   _/_  | |       */
/*                                                 <__________\______)\__)      */
/* **************************************************************************** */


#ifndef HTTP_SERVER_RESPONSEPUT_HPP
#define HTTP_SERVER_RESPONSEPUT_HPP

#include "Response.hpp"

class ResponsePut :  public Response{
public:
	ResponsePut();
	ResponsePut(RequestData &requestData, HostData *hostData);
	ResponsePut(const ResponsePut& other);
	ResponsePut& operator=(const ResponsePut &assign);
	~ResponsePut();

private:
	virtual void createBody(const std::string &uri, HostData *hostData);
	void createBody(RequestData &requestData, HostData *hostData);
	std::pair<std::string, std::string> parseBody(std::string body);
};


#endif //HTTP_SERVER_RESPONSEPUT_HPP
