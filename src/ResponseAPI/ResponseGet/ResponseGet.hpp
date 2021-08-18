#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "Response.hpp"

class ResponseGet : public Response {
	public:
		ResponseGet();

		std::string createBody();
};

#endif