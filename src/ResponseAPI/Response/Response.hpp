#ifndef RESPONSE
# define RESPONSE

# include <iostream>
# include "Request.hpp"

// Здесь понадобиться fork и excve???

class Response {
protected:
	size_t		_leftDataToSend;
	std::string	_dataToSend;
	int			_status;

public:
	Response();
	Response(const Response& other);
	Response(const Request* request);
	virtual ~Response();

	virtual std::string		createBody();
	virtual std::string		createHead();
	bool					isDone();
	const std::string		&getDataToSend() const;
	void					countSendedData(int byteSended);
};

#endif