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

class Config;

class Server {
	private:
		const Config*		_config;
		std::vector<Host>	_hosts;
	
	private:
		void	processingRequest() const;
		void	sendResponse() const;
		void	startMainProcess() const;
	
	public:
		Server();
		Server(const Config* config);

		void	start();
};

#endif