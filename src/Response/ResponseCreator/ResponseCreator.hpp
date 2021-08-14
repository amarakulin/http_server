#ifndef RESPONSE_CREATOR
# define RESPONSE_CREATOR

# include "AResponse.hpp"
# include "ResponseGet.hpp"
# include "ResponsePost.hpp"
# include "ResponseDelete.hpp"
# include "Request.hpp"

class ResponseCreator {
	private:
		ResponseGet*	createResponseGet(Request& request);
		ResponsePost*	createResponsePost(Request& request);
		ResponseDelete* createResponseDelete(Request& request);
	
	public:
		ResponseCreator();
		AResponse* createResponse(Request& request);
};

#endif