#ifndef RESPONSE_DELETE
# define RESPONSE_DELETE

#include "Response.hpp"

class ResponseDelete : public Response {
public:
	ResponseDelete();
	ResponseDelete(const ResponseDelete& other);
	ResponseDelete(RequestData& requestData);
	~ResponseDelete();

private:
	using Response::createBody;
	void createBody(const std::string &uri);
};

#endif