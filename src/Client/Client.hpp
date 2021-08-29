#ifndef CLIENT
# define CLIENT

# include <iostream>

# include "Host.hpp"
# include "Request.hpp"
#include "ResponsePost.hpp"
#include "ResponseGet.hpp"
#include "ResponseDelete.hpp"
#include "Response.hpp"

class Client {
private:
	int				_clientSocket;
	Request*		_request;
	Response*		_response;

	Client();

public:
	Client(int socket);
	Client(const Client& other);
	~Client();

	Request*	getRequest() const;
	Response*	getResponse() const;
	int			getSocket() const;
	int			getRequestStatus() const;
//	int			getResponseStatus() const;

	bool		hasResponse() const;
	bool		hasRequest() const;

	void		setResponse(Response *response);

	void		resetRequest();
	void		resetResponse();
};

#endif