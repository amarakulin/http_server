#ifndef SOCKETS
# define SOCKETS

# include <vector>
# include <poll.h>
# include <iostream>

class Sockets {
	private:
		typedef std::vector<struct pollfd>::iterator pollIter;

		std::vector<struct pollfd> 	_pollFD;
	
	public:

		Sockets();
		Sockets(const Sockets& other);
		~Sockets();

		void	addListenerSocket(int socket);
		void	addClientSocket(int socket);
		void	removeClientSocket(int socket);

		struct pollfd 	getSocketByFD(int fd);
		struct pollfd* 	getAllSockets();

		size_t			size() const;

		struct pollfd	operator[](int fd);
};

#endif