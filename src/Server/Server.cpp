#include "Server.hpp"

/*
** Constructors
*/

Server::Server() {}

Server::Server(const Config* config) : _config(config), _hosts(config->getHosts()) {}

/*
** Destructor
*/

Server::~Server() {
	delete _config;
}

/*
** Private methods
*/

struct sockaddr_in Server::createSockaddrStruct(const Host& host) {
	struct sockaddr_in 	tmp;

	tmp.sin_family = AF_INET;
	tmp.sin_port = htons(host.getPort());
	tmp.sin_addr.s_addr = inet_addr(host.getIp().c_str());

	return tmp;
}

int					Server::createListenerSocket(struct sockaddr_in addr) {
	int	listener;

	listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int opt = 1;
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	fcntl(listener, F_SETFL, O_NONBLOCK);//TODO

	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		std::cout << "Bind error" << std::endl; //TODO

	listen(listener, 5);

	return listener;
}

void				Server::startMainProcess() {
	std::vector<int>				listeners;
	std::vector<Host>::iterator		host = _hosts.begin();
	Sockets	sockets;

	for (int i = 0; i < _hosts.size(); i++, host++) {
		listeners.push_back(createListenerSocket(createSockaddrStruct(*host)));
		sockets.addListenerSocket(listeners[i]);
	}

	while (true) {
		int ret = poll(sockets.getAllSockets(), sockets.size(), 1000);
		
		if (ret == -1) {
			std::cout << "Poll error" << std::endl;
		} else if (ret == 0) {
			std::cout << "Time out" << std::endl;
		} else {
			char buf[1024];

			for (int i = listeners.size(); i < sockets.size(); i++) {
				struct pollfd client = *(sockets.getAllSockets() + i);
				if (client.revents & POLLIN) {
					ssize_t s = recv(client.fd, buf, sizeof(buf), 0);

					if (s <= 0) {
						if (s == -1)
							std::cout << "Read error: " << errno << std::endl;

						std::cout << "Close connection" << std::endl;
						// std::cout << buf << std::endl;
						close(client.fd);
						// sockets.erase(it);
						continue ;
					}

					std::cout << "/* Client in */ " << s << std::endl;
				}
			// 	//  else if ((*it).revents & POLLOUT) {
			// 	// 	std::string response = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
			// 	// 	ssize_t s = send((*it).fd, response.c_str(), response.length(), 0);
			// 	// 	// response += std::string(buf);
			// 	// 	// std::cout << s << std::endl;
			// 	// 	if (s < 0)
			// 	// 		std::cout << "Send error" << std::endl;
			// 	// 	// send((*it).fd, response.c_str(), response.length(), 0);
			// 	// 	std::cout << "/* Client out */ " << std::endl;
			// 	// }
			}

			for (int i = 0; i < listeners.size(); i++) {
				struct pollfd host = sockets.getSocketByFD(listeners[i]); //TODO optimize!!!!!!!!!!!
				if (host.revents & POLLIN) {
					int sock = accept(host.fd, NULL, NULL);
					if (sock < 0)
						std::cout << "Accept error" << std::endl;//TODO
					
					fcntl(sock, F_SETFL, O_NONBLOCK);

					sockets.addClientSocket(sock);

					std::cout << "/* Listener in */ " << sock << std::endl;
				}
			}
		}
	}
}


/*
** Public methods
*/

void	Server::start() {
	startMainProcess();
}

