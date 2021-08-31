#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "Response.hpp"
#include "RequestTypes.hpp"

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(RequestData& requestData);
	ResponseGet& operator=(const ResponseGet &assign);
	~ResponseGet();

private:
	using Response::createBody;
	virtual void	createBody(const std::string uri);


};

#endif
