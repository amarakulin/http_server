#ifndef RESPONSE
# define RESPONSE

# include <iostream>
# include "Request.hpp"

// Здесь понадобиться fork и excve???

class Response {
protected:
	size_t		_leftBytesToSend;
	std::string	_dataToSend;
	int			_status;

public:
	Response();
	Response(const Response& other);
	Response(const Request* request);
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