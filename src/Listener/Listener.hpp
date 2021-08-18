#ifndef LISTENER
# define LISTENER

# include <iostream>

# include "Host.hpp"
# include "Request.hpp"

class Listener {
	private:
		int		_socket;
		Listener();

	public:
		Listener(int host);
		Listener(const Listener& other);
		~Listener();

		int	getSocket() const;
};

#endif