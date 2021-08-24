#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "../Response/Response.hpp"
#include "../Types/RequestTypes.hpp"

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(Request *other);
	~ResponseGet();

private:
	std::string		createHead(const requestHeaderStruct& headers);
	std::string		createBody(const std::string& body);
};

#endif