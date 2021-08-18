#ifndef CLIENT
# define CLIENT

# include <iostream>

# include "Host.hpp"
# include "Request.hpp"

class Client {
	private:
		int			_clientSocket;
		Request*	_request;

		Client();

	public:
		Client(int host);
		Client(const Client& other);
		~Client();

		Request*	getRequest() const;
		int			getSocket() const;
		int			getRequsetStatus() const;

		void		resetRequest();

};

#endif