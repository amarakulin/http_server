#include "Server.hpp"

/*
** Constructors
*/

Server::Server() {}

Server::Server(const Config* config) : _config(config) {
	
	std::vector<Host*> hosts = _config->getHosts();
	for (int i = 0; i < hosts.size(); ++i) {
		std::cout << "Port: " << hosts[i]->getPort() << std::endl;
	}
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
	std::vector<Host*>			hosts = _config->getHosts();
	std::vector<Host*>::iterator host = hosts.begin();

	for (size_t i = 0; i < hosts.size(); i++, host++) {
		_listeners.push_back(Listener(createListenerSocket(createSockaddrStruct(*host))));
		_sockets.addListenerSocket(_listeners[i].getSocket()); // TODO вынести??
	}
}

struct sockaddr_in Server::createSockaddrStruct(Host* host) {
	struct sockaddr_in 	tmp;

	tmp.sin_family = AF_INET;
	tmp.sin_port = htons(host->getPort());
	tmp.sin_addr.s_addr = inet_addr(host->getIp().c_str());

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

	listen(listener, 100);

	return listener;
}

/*
** Processing client connection
*/

void Server::createNewClient(int hostSocket, HostData *hostData)
{
	try{
		int sock = accept(hostSocket, NULL, NULL); // создаем нового клиента
		if (sock > 0){
			fcntl(sock, F_SETFL, O_NONBLOCK);

			Client client(sock, hostData);
			
			_sockets.addClientSocket(sock);
			_clients.push_back(client); //TODO add method addClient
			logger.printMessage("Clients: " + std::to_string(_clients.size()));
		}
	}
	catch (std::exception &e){
		std::cout << "Got a exception: " << std::endl;
		std::cout << "|" << e.what() << "|" << std::endl;
	}
//	std::cout << "/* Listener in */ " << sock << std::endl;
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

		if (host.revents & POLLIN){
			createNewClient(host.fd, _config->getHosts()[i]->getData());
		}
	}
}

void				Server::handleClientEvents() {
	for (size_t i = _listeners.size(); i < _sockets.size(); i++) {
		struct pollfd clientPollStruct = *(_sockets.getAllSockets() + i);
		Client &client = getClientByFD(_clients, clientPollStruct.fd);

		if ((clientPollStruct.revents & POLLIN) && !client.hasResponse()) { // проверяем пришел ли запрос
			processingRequest(clientPollStruct.fd, client);
		}
		if (client.hasRequest() && !client.hasResponse()) {
			createResponse(client);
		}
		if ((clientPollStruct.revents & POLLOUT) && client.hasResponse()) {// проверяем можем ли мы отпраивть ответ
			sendResponse(clientPollStruct.fd, client);
		}
	}
}

/*
** Processing request/response
*/
void				Server::processingRequest(int clientSocket, Client& client) {
	char buf[MB]; //TODO обработать случаи, когда за один раз не получается считать
	int s = recv(clientSocket, buf, sizeof(buf), 0);
	if (s == -1){
		logger.printMessage("/* Read error */");//TODO THINK FOR TEST
//		client.getRequest()->setStatus(READED);
		bzero(buf, MB);
//		return;
	}
	if (s == 0) {
//		std::cout << "Get ziro bytes" << std::endl;
//		client.getRequest()->setStatus(READED);//TODO THINK FOR TEST
//		closeClientConnection(clientSocket);
//		bzero(buf, MB);
//		return ;
	}
	try {
		client.getRequest()->addRequestChunk(std::string(buf, s));
	} catch (BadRequestException& e) {
		 client.setResponse(_responseCreator.createResponse(ResponseError::getErrorPageStruct(BAD_REQUEST, client.getHostData()->errorPage),
															client.getHostData()));
		 client.resetRequest();
	} catch (NotAllowedException& e) {
		client.setResponse(_responseCreator.createResponse(ResponseError::getErrorPageStruct(METHOD_NOT_ALLOWED, client.getHostData()->errorPage),
															client.getHostData()));
		client.resetRequest();
	} catch (NotFoundException& e) {
		client.setResponse(_responseCreator.createResponse(ResponseError::getErrorPageStruct(NOT_FOUND, client.getHostData()->errorPage),
														   client.getHostData()));
		client.resetRequest();
	}
	bzero(buf, MB);

//	logger.printMessage("/* Client in */");
}

void				Server::createResponse(Client& client) {
	// printRequest(client.getRequest()->getData());
	try{
		client.setResponse(_responseCreator.createResponse(
				client.getRequest()->getData(), client.getHostData()));
	}
	catch (BadGatewayException& e){
		client.setResponse(_responseCreator.createResponse(
				ResponseError::getErrorPageStruct(BAD_GATE_WAY, client.getHostData()->errorPage),
				client.getHostData()));
	}
	catch (InternalServerErrorException& e){
		client.setResponse(_responseCreator.createResponse(
				ResponseError::getErrorPageStruct(INTERNAL_SERVER_ERROR, client.getHostData()->errorPage),
				client.getHostData()));
	}
	catch (NotFoundException& e){
		client.setResponse(_responseCreator.createResponse(
				ResponseError::getErrorPageStruct(NOT_FOUND, client.getHostData()->errorPage),
				client.getHostData()));
	}
	client.resetRequest();
}

void				Server::sendResponse(int clientSocket, Client& client) {
	Response *response = client.getResponse();
	size_t sendByte = countBytesToSend(response->getLeftBytesToSend());

	int byteSended = send(clientSocket, response->getDataToSend().c_str(), sendByte, 0);
//	if (byteSended < 50) {
//		std::cout << "Bytes sended: " << std::endl;
//		std::cout << response->getDataToSend().substr(0, byteSended) << std::endl;
//	}
	if (byteSended < 0){
		logger.printMessage("Send error");
	}
	response->countSendedData(byteSended);
	if (response->isDone()){
		client.resetResponse();
		std::cout << "/* Client out */ " << clientSocket << " Sended: " << byteSended << std::endl;
	}
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

size_t Server::countBytesToSend(size_t leftBytesToSend){
	if (leftBytesToSend > MB){
		leftBytesToSend = MB;
	}
	return leftBytesToSend;
}

/*
** Public methods
*/

void	Server::start() {
	startMainProcess();
}

