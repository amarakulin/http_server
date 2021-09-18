#ifndef RESPONSE_Post
# define RESPONSE_Post

#include "Response.hpp"

class ResponsePost : public Response {
public:
	ResponsePost();
	ResponsePost(RequestData &requestData, HostData *hostData);
	ResponsePost(const ResponsePost& other);
	ResponsePost& operator=(const ResponsePost &assign);
	~ResponsePost();

private:
	virtual void createBody(const std::string &uri, HostData *hostData);
	void createBody(RequestData &requestData, HostData *hostData);
	std::pair<std::string, std::string> parseBody(std::string body);
	bool	isBoundaryBody(requestHeaderStruct header);
};

#endif