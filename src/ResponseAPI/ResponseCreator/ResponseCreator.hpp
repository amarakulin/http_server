#ifndef RESPONSE_CREATOR
# define RESPONSE_CREATOR

# include <Request.hpp>
#include "Response.hpp"
#include "ResponseDelete.hpp"
#include "ResponseGet.hpp"
#include "ResponsePost.hpp"
#include "ResponseError.hpp"
#include "ResponseTypes.hpp"


Response*	createResponseGet(Request* request);
Response*	createResponsePost(Request* request);
Response*	createResponseDelete(Request* request);
Response*	createResponseError(Request* request);

static const ResponseCreatorList responseCreatorList[] ={
	{"get", &createResponseGet}, 
	{"post", &createResponsePost}, 
	{"delete", &createResponseDelete},
	{"error", &createResponseError},
	{"", nullptr}
};

class ResponseCreator {
	public:
		ResponseCreator();
		~ResponseCreator();

		Response* createResponse(Request* request);
};

#endif