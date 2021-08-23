#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "../Response/Response.hpp"

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(const Request* other);
	~ResponseGet();

private:
	std::string		createBody();
	std::string		createHead();
};

#endif