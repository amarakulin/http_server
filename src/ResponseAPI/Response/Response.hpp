#ifndef RESPONSE
# define RESPONSE

# include <iostream>
# include "Request.hpp"
# include "../../Types/ResponseTypes.hpp"

// Здесь понадобиться fork и excve???

class Response {
private:
	static const	t_response_process _arrProcessHeaders[];

	void			createHead(Request *request);
	std::string		createContentLengthHeader(std::string location);
	std::string		createHeadHeader(std::string status);
	std::string		processHeader(const std::string& headerName, const std::string& headerValue);
	static std::string		getProcessedAccept(std::string accept);

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
//	1. Find file by location
//	2. Count data by the location -> create Content-Length
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