#ifndef RESPONSE_Post
# define RESPONSE_Post

# include "AResponse.hpp"

class ResponsePost : public AResponse {
	public:
		ResponsePost();

		std::string createBody();
};

#endif