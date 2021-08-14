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
	fcntl(listener, F_SETFL, O_NONBLOCK);//TODO

	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		std::cout << "Bind error" << std::endl; //TODO

	listen(listener, 5);

	return listener;
}

void	Server::startMainProcess() {
	typedef std::vector<Host>::iterator					hostIterator;

	std::vector<int>				listeners;

	hostIterator 				host = _hosts.begin();

	int	size = _hosts.size();

	for (int i = 0; i < size; i++, host++)
		listeners.push_back(createListenerSocket(createSockaddrStruct(*host)));

	// struct pollfd fds[size];// = new pollfd[listeners.size()];
	// for (int i = 0; i < size; i++) {
	// 	// if (i < size) {
	// 		fds[i].fd = listeners[i];
	// 		fds[i].events = POLLIN;
	// 	// } else {
	// 	// 	fds[i].fd = listeners[i - size];
	// 	// 	fds[i].events = POLLOUT;
	// 	// }
	// }

	// while (true) {
	// 	int ret = poll(fds, size, 1000);
	// 	// проверяем успешность вызова
	// 	if (ret == -1) {

	// 		// ошибка
	// 		std::cout << "Error" << std::endl;
	// 	}
	// 	else if (ret == 0) {

	// 		// таймаут, событий не произошло
	// 		std::cout << "Time out" << std::endl;
	// 	}
	// 	else {
	// 		char buf[10];

	// 		// обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
	// 		for (int i = 0; i < size; i++) {
	// 			if (fds[i].revents & POLLIN) {
	// 				fds[i].revents = 0;

	// 				int sock = accept(fds[i].fd, NULL, NULL);
	// 				if (sock < 0)
	// 					std::cout << "Accept error" << std::endl;
					
	// 				fcntl(sock, F_SETFL, O_NONBLOCK);

	// 				ssize_t s = read(fds[i].fd, buf, sizeof(buf));

	// 				std::cout << s << std::endl;
	// 				std::cout << "/* message */" << std::endl;
	// 				// обработка входных данных от sock1
	// 			} else if (fds[i].revents & POLLOUT) {
	// 				fds[i].revents = 0;
	// 				std::cout << "/* out */" << std::endl;
	// 				// обработка исходящих данных от sock2
	// 			}
	// 		}
	// 	}
	// }
}


/*
** Public methods
*/

void	Server::start() {
	startMainProcess();
}

