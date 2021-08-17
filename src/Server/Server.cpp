#include "Server.hpp"
#include "../utils/utils.hpp"

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
	Sockets							sockets;

	std::vector<Client>				clients;

	for (size_t i = 0; i < _hosts.size(); i++, host++) {
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
			char buf[20];

			for (size_t i = 0; i < listeners.size(); i++) {
				struct pollfd host = sockets.getSocketByFD(listeners[i]); //TODO optimize!!!!!!!!!!!
				if (host.revents & POLLIN) {
					int sock = accept(host.fd, NULL, NULL); // создаем нового клиента
					if (sock < 0)
						std::cout << "Accept error" << std::endl;//TODO
					
					fcntl(sock, F_SETFL, O_NONBLOCK);

					Client client(sock);

					sockets.addClientSocket(sock);
					clients.push_back(client); //TODO add method addClient

					std::cout << "/* Listener in */ " << sock << std::endl;
				}
			}

			for (size_t i = listeners.size(); i < sockets.size(); i++) {
				struct pollfd clientPollStruct = *(sockets.getAllSockets() + i);
				Client client = getClientByFD(clients, clientPollStruct.fd);

				if (clientPollStruct.revents & POLLIN) { // проверяем пришел ли запрос
					int s = recv(clientPollStruct.fd, buf, sizeof(buf), 0);



//					std::cout << "Data: |" << client.getRequest()->getData() << "|" << std::endl;
					client.getRequest()->addRequestChunk(std::string(buf));
					bzero(buf, strlen(buf));
					// buf[s] = '\0';

					 if (s == -1)
					 	std::cout << "Read error: " << s << std::endl;

//					 if (s == 0) {
//					 	std::cout << "Close connection: " << s <<  std::endl;
//					 	close(client.fd);
//					 	sockets.removeClientSocket(client.fd);
//					 	continue ;
//					 }

					std::cout << "/* Client in */ " << clientPollStruct.fd << " bufSize: " << s  << std::endl;
				}


				if ((clientPollStruct.revents & POLLOUT)
					&& clients.size()
					&& client.getRequest()->isDone()) { // проверяем можем ли мы отпраивть ответ
					std::string response = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><script src='index.js'></script></body></html>";
//					 std::string response = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
					int s = send(clientPollStruct.fd, response.c_str(), response.length(), 0);

					if (s < 0)
						std::cout << "Send error" << std::endl;

					std::cout << "/* Client out */ " << clientPollStruct.fd << std::endl;
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

