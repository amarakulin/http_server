#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "../Response/Response.hpp"
#include "../Types/RequestTypes.hpp"

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(Request *other);
	ResponseGet& operator=(const ResponseGet &assign);
	~ResponseGet();

private:
	std::string		createHead(Request *request);
	std::string		createBody(const std::string& body);
	std::string		createContentLengthHeader(std::string body);
	std::string		createHeadHeader(std::string status);


	std::string		processHeader(const std::string& headerName, const std::string& headerValue);
	std::string		handlerMethod(const std::string& method);
	std::string		handlerHost(const std::string& host);
	std::string		handlerLocation(const std::string& location);
	std::string		handlerProtocol(const std::string& protocol);


};

#endif