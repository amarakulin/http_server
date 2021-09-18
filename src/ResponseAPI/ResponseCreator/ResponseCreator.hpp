#ifndef RESPONSE_CREATOR
# define RESPONSE_CREATOR

# include <Request.hpp>
#include "Global.hpp"
#include "Response.hpp"
#include "ResponseDelete.hpp"
#include "ResponseGet.hpp"
#include "ResponsePut.hpp"
#include "ResponsePost.hpp"
#include "ResponseHead.hpp"
#include "ResponseError.hpp"
#include "ResponseTypes.hpp"


Response *createResponseGet(RequestData &requestData, HostData *hostData);
Response *createResponsePut(RequestData &requestData, HostData *hostData);
Response *createResponsePost(RequestData &requestData, HostData *hostData);
Response *createResponseHead(RequestData &requestData, HostData *hostData);
Response *createResponseDelete(RequestData &requestData, HostData *hostData);


static const ResponseCreatorList responseCreatorList[] ={
	{"get", &createResponseGet},
	{"put", &createResponsePut},
	{"post", &createResponsePost},
	{"head", &createResponseHead},
	{"delete", &createResponseDelete},
	{"", nullptr}
};

class ResponseCreator {
	public:
		ResponseCreator();
		~ResponseCreator();

		Response *createResponse(RequestData &requestData, HostData *hostData);
		Response *createResponse(const ErrorPage &errorPage, HostData *hostData);

};

#endif