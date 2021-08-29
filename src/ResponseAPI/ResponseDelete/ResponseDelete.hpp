#ifndef RESPONSE_DELETE
# define RESPONSE_DELETE

#include "Response.hpp"

class ResponseDelete : public Response {
	public:
		ResponseDelete();
		ResponseDelete(const ResponseDelete& other);
		ResponseDelete(Request* other);
		~ResponseDelete();

		std::string createBody();
};

#endif