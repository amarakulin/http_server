#ifndef RESPONSE_Post
# define RESPONSE_Post

#include "Response.hpp"

class ResponsePost : public Response {
	public:
		ResponsePost();
		ResponsePost(Request* other);
		ResponsePost(const ResponsePost& other);
		~ResponsePost();

		std::string createBody();
};

#endif