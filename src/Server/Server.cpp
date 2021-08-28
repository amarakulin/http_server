#include "Server.hpp"

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
** Creating listenters
*/

void				Server::createListeners() {
	std::vector<Host>			hosts = _config->getHosts();
	std::vector<Host>::iterator host = hosts.begin();

	for (size_t i = 0; i < hosts.size(); i++, host++) {
		_listeners.push_back(Listener(createListenerSocket(createSockaddrStruct(*host))));
		_sockets.addListenerSocket(_listeners[i].getSocket()); // TODO вынести??
	}
}

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

/*
** Processing client connection
*/

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

void				Server::closeClientConnection(int clientSocket) {
	std::vector<Client>::iterator client = _clients.begin();
	
	std::cout << "Close connection with: " << clientSocket <<  std::endl;
	close(clientSocket);
	_sockets.removeClientSocket(clientSocket);
	for (; client != _clients.end(); client++) {
		if ((*client).getSocket() == clientSocket) {
			_clients.erase(client);
			break ;
		}
	}
}

/*
** Main Process
*/

void				Server::startMainProcess() {
	while (true) {
		int ret = poll(_sockets.getAllSockets(), _sockets.size(), -1);
		
		if (ret == -1) {
			std::cout << "Poll error" << std::endl;
		} else if (ret > 0) {
			handleListenerEvents();
			handleClientEvents();
		}
	}
}

/*
** Event handlers
*/

void				Server::handleListenerEvents() {
	for (size_t i = 0; i < _listeners.size(); i++) {
		struct pollfd host = _sockets.getSocketByFD(_listeners[i].getSocket()); //TODO optimize!!!!!!!!!!!

		if (host.revents & POLLIN)
			createNewClient(host.fd);
	}
}

void				Server::handleClientEvents() {
	for (size_t i = _listeners.size(); i < _sockets.size(); i++) {
		struct pollfd clientPollStruct = *(_sockets.getAllSockets() + i);
		Client client = getClientByFD(_clients, clientPollStruct.fd);

		if ((clientPollStruct.revents & POLLIN) && !client.hasResponse()) // проверяем пришел ли запрос
			processingRequest(clientPollStruct.fd, client);
		
		if (client.hasRequest() && !client.hasResponse()) //TODO pichkasik
			createResponse(client);

		if ((clientPollStruct.revents & POLLOUT) && client.hasResponse())// проверяем можем ли мы отпраивть ответ
			sendResponse(clientPollStruct.fd, client);
	}
}

/*
** Processing request/response
*/

void				Server::processingRequest(int clientSocket, Client& client) {
	char buf[MB]; //TODO обработать случаи, когда за один раз не получается считать
	int s = recv(clientSocket, buf, sizeof(buf), 0);

	if (s == -1)
		std::cout << "Read error: " << s << std::endl;

	if (s == 0) {
		closeClientConnection(clientSocket);
		return ;
	}
	try {
		client.getRequest()->addRequestChunk(buf);
	} catch (BadRequestException& e) {
		//TODO
		// client.setResponse(_responseCreator.createResponse(400));
		// client.resetRequest();
	} catch (NotAllowedException& e) {
		//TODO
		// client.setResponse(_responseCreator.createResponse(405));
		// client.resetRequest();
	}
	bzero(buf, MB);

	std::cout << "/* Client in */ "  << std::endl;
}

void				Server::createResponse(Client& client) {
	client.setResponse(_responseCreator.createResponse(client.getRequest()));
	client.resetRequest();
}

void				Server::sendResponse(int clientSocket, Client& client) {
	// std::string response = "HTTP/1.1 200 OK\r\nContent-length: 436\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><form method='POST' action='127.0.0.1'><input name='value' value='key' placeholder='TEST'><button>POST</button></form><script src='index.js'></script></body></html>";
	// std::string response = "HTTP/1.1 200 OK\r\nContent-length: 318\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title><link rel='stylesheet' href='index.css'></head><body><h2>Hello</h2><script src='index.js'></script></body></html>";
	std::string response = "HTTP/1.1 200 OK\r\nContent-length: 5\r\nContent-type: text/html\r\nDate: Wed, 21 Oct 2015 07:28:00 GMT\r\n\r\n12345";
	std::cout << "!!!Response: " << client.getResponse()->getDataToSend() << std::endl;
	int s = send(clientSocket,
				 client.getResponse()->getDataToSend().c_str(),
				 client.getResponse()->getDataToSend().length(),
				 0);
	// int s = client.sendResponse(); // отправка response //TODO pichkasik   Вот тут я чутка не понимаю как отправлять кусками

	if (s < 0)
		std::cout << "Send error" << std::endl;

	// if (client.isResponseSended()){ // отчистка  //TODO pichkasik
	client.resetResponse();

	std::cout << "/* Client out */ " << clientSocket << " Sended: " << s << std::endl;
}

/*
** Support
*/

Client& 			Server::getClientByFD(std::vector<Client>& clients, int fd) {
	std::vector<Client>::iterator it = clients.begin();

	for (; it != clients.end(); it++) {
		if ((*it).getSocket() == fd)
			return *it;
	}	
	return *it;
}

/*
** Public methods
*/

void	Server::start() {
	startMainProcess();
}

