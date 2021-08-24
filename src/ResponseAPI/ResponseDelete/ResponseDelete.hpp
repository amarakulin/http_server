#ifndef RESPONSE_DELETE
# define RESPONSE_DELETE

//# include "Response.hpp"

#include "../Response/Response.hpp"

class ResponseDelete : public Response {
	public:
		ResponseDelete();
		ResponseDelete(const ResponseDelete& other);
		ResponseDelete(const Request* other);
		~ResponseDelete();

		std::string createBody();
};

#endif