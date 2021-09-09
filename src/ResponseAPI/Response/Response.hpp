#ifndef RESPONSE
# define RESPONSE

# include <iostream>
#include <HostTypes.hpp>
# include "Request.hpp"

# include "ResponseTypes.hpp"
# include "utils.hpp"

// Здесь понадобиться fork и excve???

static const std::pair<int, std::string> arrResponseStatuses [] = {
		std::pair<int, std::string>(200, "OK"),
		std::pair<int, std::string>(201, "Created"),
		std::pair<int, std::string>(204, "No Content"),
		std::pair<int, std::string>(300, "Multiple Choice"),
		std::pair<int, std::string>(301, "Moved Permanently"),
		std::pair<int, std::string>(302, "Found"),
		std::pair<int, std::string>(303, "See Other"),
		std::pair<int, std::string>(304, "Not Modified"),
		std::pair<int, std::string>(400, "Bad Request"),
		std::pair<int, std::string>(403, "Forbidden"),
		std::pair<int, std::string>(404, "Not Found"),
		std::pair<int, std::string>(405, "Method Not Allowed"),
		std::pair<int, std::string>(500, "Internal Server Error"),
		std::pair<int, std::string>(501, "Not Implemented"),
		std::pair<int, std::string>(502, "Bad Gateway"),
		std::pair<int, std::string>(505, "HTTP Version Not Supported"),


		std::pair<int, std::string>(0, ""),
};

class Response {
private:
	static const	t_response_process _arrProcessHeaders[];

	std::string		createHeadHeader();
	std::string		createRedirectHeader(HostData *hostData); //TODO handle 3xx status code
	std::string		processHeader(const std::string& headerName, const std::string& headerValue);
	static std::string		getContentTypeHeader(std::string accept);
	static std::string		getContentLengthHeader(std::string uri);

	//TODO Workout default paths
	//TODO Workout redirection
	//TODO Workout data for CGI
	//TODO Put method


protected:
	size_t		_leftBytesToSend;
	std::string	_dataToSend;
	int			_state;
	int			_status;

	void createHead(RequestData &requestData, HostData *hostData);
	virtual void	createBody(const std::string& uri);
	void			changeContentLength(size_t valueContentLength);

public:
	Response();
	Response(const Response& other);
	Response(RequestData &requestData, HostData *hostData);
	Response& operator=(const Response &assign);
	virtual ~Response();

	bool					isDone();
	void					countSendedData(int byteSended);

/*
** Getters
*/
	virtual size_t			getLeftBytesToSend() const;
	const std::string		&getDataToSend() const;
	virtual int				getStatus() const;

	int getState() const;

/*
** Setters
*/
};

#endif