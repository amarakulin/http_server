#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "AResponse.hpp"

class ResponseGet : public AResponse {
	public:
		ResponseGet();

		std::string createBody();
};

#endif