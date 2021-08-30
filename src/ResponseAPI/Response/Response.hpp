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
	std::string		createContentLengthHeader(std::string location);
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