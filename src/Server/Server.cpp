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
		int ret = poll(&(client.front()), size, 1000);
		// проверяем успешность вызова
		if (ret == -1) {
			std::cout << "Error" << std::endl;
		} else if (ret == 0) {
			// std::cout << "Time out" << std::endl;
		} else {
			char buf[10];

			for (int i = 0; i < listeners.size(); i++) {
				if (client[i].revents & POLLIN) {
					client[i].revents = 0;

					int sock = accept(client[i].fd, NULL, NULL);
					if (sock < 0)
						std::cout << "Accept error" << std::endl;
					
					fcntl(sock, F_SETFL, O_NONBLOCK);

					struct pollfd tmp;
					tmp.fd = sock;
					tmp.events = POLLIN | POLLOUT;
					client.push_back(tmp);

					std::cout << "/* Listener in */" << std::endl;

				} else if (client[i].revents & POLLOUT) {
					client[i].revents = 0;
					std::cout << "/* Listener out */" << std::endl;
				}
			}

			for (int i = listeners.size(); i < client.size(); i++) {
				std::cout << "FD: " << client[i].fd << " Events: " << client[i].events << " Revents: " << client[i].revents << std::endl;
			}


			for (std::vector<struct pollfd>::iterator it = client.begin() + listeners.size(); it != client.end(); it++) {
				if ((*it).revents & POLLIN) {
					(*it).revents = 0;

					ssize_t s = read((*it).fd, buf, sizeof(buf));

					std::cout << s << std::endl;

					std::cout << "/* Client in */" << std::endl;
					
				} else if ((*it).revents & POLLOUT) {
					(*it).revents = 0;
					write((*it).fd, "HTTP/1.1 200 OK\r\nContent-length: 5\r\n\r\n12345", 43);
					std::cout << "/* Client out */" << std::endl;

					std::cout << "Close fd: " << (*it).fd << std::endl;
					close((*it).fd);
					// client.erase(it);
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

