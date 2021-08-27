#ifndef RESPONSE_GET
# define RESPONSE_GET

# include "../Response/Response.hpp"
#include "../Types/RequestTypes.hpp"

typedef struct {
	const char*		nameHeader;
	std::string			(*getProcessedHeader)(const std::string &valueHeader);
}		t_response_process;

class ResponseGet : public Response {
public:
	ResponseGet();
	ResponseGet(const ResponseGet& other);
	ResponseGet(Request *other);
	ResponseGet& operator=(const ResponseGet &assign);
	~ResponseGet();

private:
	static const	t_response_process _arrProcessHeaders[];
	void		createHead(Request *request);
	void		createBody(const std::string& body);
	std::string		createContentLengthHeader(std::string body);
	std::string		createHeadHeader(std::string status);


	std::string		processHeader(const std::string& headerName, const std::string& headerValue);

	static std::string		getProcessedMethod(const std::string& method);
	static std::string		getProcessedHost(const std::string& host);
	static std::string		getProcessedLocation(const std::string& location);
	static std::string		getProcessedProtocol(const std::string& protocol);


};

#endif
