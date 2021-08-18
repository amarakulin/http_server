#ifndef RESPONSE_CREATOR
# define RESPONSE_CREATOR

#include <Request.hpp>
#include "../ResponseGet/ResponseGet.hpp"
#include "../ResponsePost/ResponsePost.hpp"
#include "../ResponseDelete/ResponseDelete.hpp"
#include "../Response/Response.hpp"

class ResponseCreator {
	private:
		ResponseGet*	createResponseGet(Request* request);
		ResponsePost*	createResponsePost(Request* request);
		ResponseDelete* createResponseDelete(Request* request);
	
	public:
		ResponseCreator();
		~ResponseCreator();

		Response* createResponse(Request* request);
};

#endif