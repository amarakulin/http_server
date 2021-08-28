#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "../Response/Response.hpp"
#include "../Types/RequestTypes.hpp"

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(Request *request);
	ResponseGet& operator=(const ResponseGet &assign);
	~ResponseGet();

private:
	void		createBody(const std::string& body);


};

#endif
