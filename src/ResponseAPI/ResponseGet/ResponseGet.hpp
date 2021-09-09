#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "Response.hpp"
#include "RequestTypes.hpp"

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(RequestData &requestData, HostData *hostData);
	ResponseGet& operator=(const ResponseGet &assign);
	~ResponseGet();

private:
	virtual void	createBody(const std::string& uri);


};

#endif
