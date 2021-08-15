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

	int	size = _hosts.size();

	for (int i = 0; i < size; i++, host++)
		listeners.push_back(createListenerSocket(createSockaddrStruct(*host)));

	std::vector<struct pollfd> client;

	client.reserve(size);

	for (int i = 0; i < size; i++) {
		struct pollfd tmp;
		tmp.fd = listeners[i];
		tmp.events = POLLIN | POLLOUT;
		client.push_back(tmp);
	}

	while (true) {
		int ret = poll(&(client.front()), client. size(), 1000);
		// проверяем успешность вызова
		if (ret == -1) {
			std::cout << "Error" << std::endl;
		} else if (ret == 0) {
			std::cout << "Time out" << std::endl;
		} else {
			char buf[1000];

			for (int i = 0; i < listeners.size(); i++) {
				if (client[i].revents & POLLIN) {
					int sock = accept(client[i].fd, NULL, NULL);
					if (sock < 0)
						std::cout << "Accept error" << std::endl;
					
					fcntl(sock, F_SETFL, O_NONBLOCK);

					struct pollfd tmp;
					tmp.fd = sock;
					tmp.events = POLLIN | POLLOUT;
					client.push_back(tmp);

					std::cout << "/* Listener in */ " << sock << std::endl;

				} else if (client[i].revents & POLLOUT) {
					// client[i].revents = 0;
					std::cout << "/* Listener out */" << std::endl;
				}
			}

			// for (std::vector<struct pollfd>::iterator it = client.begin() + listeners.size(); it != client.end(); it++) {
			// 	std::cout << "FD: " << (*it).fd << " Events: " << (*it).events << " Revents: " << (*it).revents << std::endl;
			// }
			// usleep(1000);


			for (std::vector<struct pollfd>::iterator it = client.begin() + listeners.size(); it != client.end(); it++) {
				if ((*it).revents & POLLIN) {
					ssize_t s = recv((*it).fd, buf, sizeof(buf), 0);

					if (s <= 0) {
						if (s == -1)
							std::cout << "Read error: " << errno << std::endl;

						std::cout << "Close connection" << std::endl;
						close((*it).fd);
						// client.erase(it);
						continue ;
					}

					// std::string request = "HTTP/1.1 200 OK\r\nContent-length: 662\r\n\r\n";
					// request += std::string(buf);
					// send((*it).fd, request.c_str(), request.length(), 0);


					std::cout << "/* Client in */ " << s << std::endl;
					
				} else if ((*it).revents & POLLOUT) {
					std::string response = "HTTP/1.1 200 OK\r\nContent-length: 5\r\n\r\n12345";
					ssize_t s = send((*it).fd, response.c_str(), response.length(), 0);
					// response += std::string(buf);
					// std::cout << buf << std::endl;
					// if (s < 0)
					// 	std::cout << "Send error" << std::endl;
					// send((*it).fd, response.c_str(), response.length(), 0);
					std::cout << "/* Client out */ " << std::endl;
				}
			}

			// for (int i = listeners.size(); i < client.size(); i++) {
			// 	if (client[i].revents & POLLIN) {
			// 		client[i].revents = 0;

			// 		// int sock = accept(client[i].fd, NULL, NULL);
			// 		// std::cout << sock << std::endl;
			// 		// if (sock < 0)
			// 		// 	std::cout << "Accept error" << std::endl;
					
			// 		// fcntl(sock, F_SETFL, O_NONBLOCK);

			// 		// struct pollfd tmp;
			// 		// tmp.fd = sock;
			// 		// tmp.events = POLLIN | POLLOUT;
			// 		// client.push_back(tmp);

			// 		ssize_t s = read(client[i].fd, buf, sizeof(buf));

			// 		std::cout << s << std::endl;

			// 		std::cout << "/* Client in */" << std::endl;
					
			// 		// std::vector<struct pollfd>::iterator it = client.begin();
			// 		// for (;&(*it) != &(client[i]) || it != client.end(); it++) ;
			// 		// client.erase(it);
			// 		// close(client[i].fd);
			// 		// close(sock);

			// 	} else if (client[i].revents & POLLOUT) {
			// 		client[i].revents = 0;
			// 		write(client[i].fd, "HTTP/1.1 200 OK\r\nContent-length: 5\r\n\r\n12345", 43);
			// 		std::cout << "/* Client out */" << std::endl;

			// 		// std::vector<struct pollfd>::iterator it = client.begin();
			// 		// for (;&(*it) != &(client[i]) || it != client.end(); it++) ;
			// 		// std::cout << "Close fd: " << (*it).fd << std::endl;
			// 		// client.erase(it);
			// 		// close(client[i].fd);
			// 	}
			// }
		}
	}
}


/*
** Public methods
*/

void	Server::start() {
	startMainProcess();
}

