#ifndef RESPONSE_Post
# define RESPONSE_Post

# include "Response.hpp"

class ResponsePost : public Response {
	public:
		ResponsePost();

		std::string createBody();
};

#endif