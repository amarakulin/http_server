#ifndef RESPONSE
# define RESPONSE

# include <iostream>
# include "Request.hpp"

# include "ResponseTypes.hpp"
# include "utils.hpp"

// Здесь понадобиться fork и excve???

class Response {
private:
	static const	t_response_process _arrProcessHeaders[];

	void			createHead(Request *request);
	std::string		createContentLengthHeader(std::string uri);
	std::string		createHeadHeader();
	std::string		processHeader(const std::string& headerName, const std::string& headerValue);
	static std::string		getProcessedAccept(std::string accept);
	//TODO figure out how works redirect and how to understand if response has to be with status 3xx
	//TODO figure out about root location (/) and if I got a dir_path in uri
	//TODO Ask about another headers
	//TODO 
	//TODO CGI env variable

protected:
	size_t		_leftBytesToSend;
	std::string	_dataToSend;
	int			_state;

public:
	Response();
	Response(const Response& other);
	Response(Request *request);
	Response& operator=(const Response &assign);
	virtual ~Response();

//TODO
//	0. Create status code
//	1. Find file by uri
//	2. Count data by the uri -> create Content-Length
//	3. Process another headers

	bool					isDone();
	void					countSendedData(int byteSended);

/*
** Getters
*/
	virtual size_t			getLeftBytesToSend() const;
	const std::string		&getDataToSend() const;
	virtual int				getStatus() const;

/*
** Setters
*/
};

#endif