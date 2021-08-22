#ifndef RESPONSE
# define RESPONSE

# include <iostream>
# include "Request.hpp"

// Здесь понадобиться fork и excve???

class Response {
protected:
	size_t		_leftDataToSend;
	std::string	_dataToSend;

public:
	Response();
	Response(const Response& other);
	Response(const Request* request);
	virtual ~Response();

	virtual std::string		createBody();
	virtual std::string		createHead();

	const std::string &getDataToSend() const;
};

#endif