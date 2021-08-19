#ifndef CLIENT
# define CLIENT

# include <iostream>

# include "Host.hpp"
# include "Request.hpp"
#include "../ResponseAPI/Response/Response.hpp"
#include "../ResponseAPI/Response/Response.hpp"

class Client {
private:
	int				_clientSocket;
	Request*		_request;
	Response*		_response;

	Client();

public:
	Client(int host);
	Client(const Client& other);
	~Client();

	Request*	getRequest() const;
	int			getSocket() const;
	int			getRequestStatus() const;
	int			getResponseStatus() const;

	void		setResponse(Response *response);

	void		resetRequest();
	void		resetResponse();
	int			sendResponse();

	bool		isResponseSended();
	bool		isResponseEmpty();
};

#endif