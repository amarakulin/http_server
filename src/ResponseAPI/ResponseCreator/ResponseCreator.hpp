#ifndef RESPONSE_CREATOR
# define RESPONSE_CREATOR

# include <Request.hpp>
#include "Response.hpp"
#include "ResponseDelete.hpp"
#include "ResponseGet.hpp"
#include "ResponsePost.hpp"
#include "ResponseError.hpp"
#include "ResponseTypes.hpp"


Response*	createResponseGet(RequestData& requestData);
Response*	createResponsePost(RequestData& requestData);
Response*	createResponseDelete(RequestData& requestData);

static const ResponseCreatorList responseCreatorList[] ={
	{"get", &createResponseGet}, 
	{"post", &createResponsePost}, 
	{"delete", &createResponseDelete},
	{"", nullptr}
};

class ResponseCreator {
	public:
		ResponseCreator();
		~ResponseCreator();

		Response* createResponse(RequestData& requestData);
		Response* createResponse(const ErrorPage &errorPage);

};

#endif