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
# include <map>

# include "Config.hpp"
# include "Request.hpp"
# include "Host.hpp"
# include "Client.hpp"
# include "Listener.hpp"
# include "Sockets.hpp"

# include "utils.hpp"

# define MB 1048576


class Config;

class Server {
	private:
		const Config*		_config;

		std::vector<Client>		_clients;
		std::vector<Listener>	_listeners;
		Sockets					_sockets;
	
	private:
		void	processingRequest() const;
		void	sendResponse() const;

	private:
		void				startMainProcess();

		void				createNewClient(int hostSocket);
		void				closeClientConnection(int clientSocket);

		void				createListeners();
		struct sockaddr_in	createSockaddrStruct(const Host& host);
		int					createListenerSocket(struct sockaddr_in addr);
	
		Server();

	public:
		Server(const Config* config);
		~Server();

		void	start();
};

#endif