#ifndef CLIENT
# define CLIENT

# include <iostream>

# include "Host.hpp"
# include "Request.hpp"
# include "Response.hpp"

class Client {
	private:
		int			_clientSocket;
		Request*	_request;
		Response*	_response;

		Client();

	public:
		Client(int host);
		Client(const Client& other);
		~Client();

		Request*	getRequest() const;
		int			getSocket() const;
		int			getRequestStatus() const;

		void		resetRequest();

};

#endif