#ifndef RESPONSE_Post
# define RESPONSE_Post

#include "Response.hpp"

class ResponsePost : public Response {
public:
	ResponsePost();
	ResponsePost(RequestData& requestData);
	ResponsePost(const ResponsePost& other);
	ResponsePost& operator=(const ResponsePost &assign);
	~ResponsePost();

private:
	virtual void createBody(const std::string& uri);
	std::string getDataFromCGI(const std::string& uri);
};

#endif