/* **************************************************************************** */
/*                                                                      .       */
/*   ResponseHead.hpp                                                        / V\     */
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


#ifndef HTTP_SERVER_RESPONSEHEAD_HPP
#define HTTP_SERVER_RESPONSEHEAD_HPP

# include "Response.hpp"
#include "RequestTypes.hpp"

class ResponseHead : public Response {
public:
	ResponseHead();
	ResponseHead(const ResponseHead& other);
	ResponseHead(RequestData &requestData, HostData *hostData);
	ResponseHead& operator=(const ResponseHead &assign);
	~ResponseHead();

private:
	virtual void createBody(const std::string &uri, HostData *hostData);


};


#endif //HTTP_SERVER_RESPONSEHEAD_HPP
