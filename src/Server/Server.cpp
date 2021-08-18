#include "Server.hpp"
#include "../utils/utils.hpp"

/*
** Constructors
*/

Server::Server() {}

Server::Server(const Config* config) : _config(config) {
	createListeners();
}

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

void				Server::createListeners() {
	std::vector<Host>			hosts = _config->getHosts();
	std::vector<Host>::iterator host = hosts.begin();

	for (size_t i = 0; i < hosts.size(); i++, host++) {
		_listeners.push_back(Listener(createListenerSocket(createSockaddrStruct(*host))));
		_sockets.addListenerSocket(_listeners[i].getSocket()); // TODO вынести??
	}
}

void				Server::createNewClient(int hostSocket) {
	int sock = accept(hostSocket, NULL, NULL); // создаем нового клиента
	if (sock < 0)
		std::cout << "Accept error" << std::endl;//TODO
	
	fcntl(sock, F_SETFL, O_NONBLOCK);

	Client client(sock);

	_sockets.addClientSocket(sock);
	_clients.push_back(client); //TODO add method addClient

	std::cout << "/* Listener in */ " << sock << std::endl;
}

void				Server::startMainProcess() {
	while (true) {
		int ret = poll(_sockets.getAllSockets(), _sockets.size(), 1000);
		
		if (ret == -1) {
			std::cout << "Poll error" << std::endl;
		} else if (ret == 0) {
			std::cout << "Time out" << std::endl;
		} else {
			char buf[MB]; //TODO обработать случаи, когда за один раз не получается считать/отправить

			for (size_t i = 0; i < _listeners.size(); i++) {
				struct pollfd host = _sockets.getSocketByFD(_listeners[i].getSocket()); //TODO optimize!!!!!!!!!!!
				
				if (host.revents & POLLIN)
					createNewClient(host.fd);
			}

			for (size_t i = _listeners.size(); i < _sockets.size(); i++) {
				struct pollfd clientPollStruct = *(_sockets.getAllSockets() + i);
				Client client = getClientByFD(_clients, clientPollStruct.fd);

				if (clientPollStruct.revents & POLLIN) { // проверяем пришел ли запрос
					int s = recv(clientPollStruct.fd, buf, sizeof(buf), 0);

					// if (s == -1)
					// 	std::cout << "Read error: " << s << std::endl;

					// if (s == 0) {
					//  	std::cout << "Close connection: " << s <<  std::endl;
					//  	close(clientPollStruct.fd);
					//  	sockets.removeClientSocket(clientPollStruct.fd);
					// 	// _clients.erase(client);
					//  	continue ;
					// }

					client.getRequest()->addRequestChunk(buf);
					bzero(buf, strlen(buf));


					std::cout << "/* Client in */ " << clientPollStruct.fd << " bufSize: " << s << " Data: |" << client.getRequest()->getData() << "|" << std::endl;
					// std::cout << "/* Client in */ " << clientPollStruct.fd << " bufSize: " << s << " Data: |" << buf << "|" << std::endl;
				}


				if ((clientPollStruct.revents & POLLOUT) && client.getRequestStatus() == DONE) { // проверяем можем ли мы отпраивть ответ
					std::string response = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><script src='index.js'></script></body></html>";
					// std::string response = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
					int s = send(clientPollStruct.fd, response.c_str(), response.length(), 0);

					if (s < 0)
						std::cout << "Send error" << std::endl;

					std::cout << "/* Client out */ " << clientPollStruct.fd << std::endl;
					client.resetRequest();
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

