#ifndef SERVER
# define SERVER

# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <functional>

# include <vector>

# include "Config.hpp"
# include "Request.hpp"
# include "Host.hpp"
# include "Sockets.hpp"


class Config;

class Server {
	private:
		const Config*		_config;
		std::vector<Host>	_hosts;
	
	private:
		void	processingRequest() const;
		void	sendResponse() const;
		void	startMainProcess();

	private:
		struct sockaddr_in	createSockaddrStruct(const Host& host);
		int					createListenerSocket(struct sockaddr_in addr);

		void				createClientPairForPoll();
	
	public:
		Server();
		Server(const Config* config);
		~Server();

		void	start();
};

#endif