#ifndef RESPONSE_DELETE
# define RESPONSE_DELETE

# include "Response.hpp"

class ResponseDelete : public Response {
	public:
		ResponseDelete();

		std::string createBody();
};

#endif