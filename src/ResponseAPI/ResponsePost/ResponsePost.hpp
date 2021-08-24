#ifndef RESPONSE_Post
# define RESPONSE_Post

//# include "Response.hpp"


//FOR Debug for lovely Clion
#include "../Response/Response.hpp"

class ResponsePost : public Response {
	public:
		ResponsePost();
		ResponsePost(const Request* other);
		ResponsePost(const ResponsePost& other);
		~ResponsePost();

		std::string createBody();
};

#endif