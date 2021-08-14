#ifndef RESPONSE_DELETE
# define RESPONSE_DELETE

# include "AResponse.hpp"

class ResponseDelete : public AResponse {
	public:
		ResponseDelete();

		std::string createBody();
};

#endif