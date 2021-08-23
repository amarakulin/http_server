#include "Sockets.hpp"

Sockets::Sockets() {}

Sockets::~Sockets() {}

void	Sockets::addListenerSocket(int socket) {
	struct pollfd tmpListener;

	tmpListener.fd = socket;
	tmpListener.events = POLLIN;

	_pollFD.push_back(tmpListener);
}

void	Sockets::addClientSocket(int socket) {
	struct pollfd tmpClient;

	tmpClient.fd = socket;
	tmpClient.events = POLLIN | POLLOUT;

	_pollFD.push_back(tmpClient);
}

void	Sockets::removeClientSocket(int socket) {
	pollIter it = _pollFD.begin();
	for (;it != _pollFD.end(); it++) {
		if ((*it).fd == socket) {
			_pollFD.erase(it);
			return ;
		}
	}
}

struct pollfd 	Sockets::getSocketByFD(int fd) {
	pollIter it = _pollFD.begin();
	for (; (*it).fd != fd && it != _pollFD.end(); it++) ;
	return *it;
}

struct pollfd* 	Sockets::getAllSockets() {
	return &(_pollFD.front());
}

size_t				Sockets::size() const {
	return _pollFD.size();
}

struct pollfd	Sockets::operator[](int fd) {
	pollIter it = _pollFD.begin();
	for (; (*it).fd != fd || it != _pollFD.end(); it++) ;
	return *it;
}