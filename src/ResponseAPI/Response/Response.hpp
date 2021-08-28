#ifndef RESPONSE
# define RESPONSE

# include <iostream>
# include "Request.hpp"

// Здесь понадобиться fork и excve???

class Response {
protected:
	size_t		_leftBytesToSend;
	std::string	_dataToSend;
	int			_state;

	virtual void		createHead();

public:
	Response();
	Response(const Response& other);
	Response(const Request* request);
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