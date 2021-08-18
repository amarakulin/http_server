#include "Listener.hpp"

Listener::Listener(int socket) : _socket(socket) {}

Listener::Listener(const Listener& other) : _socket(other._socket) {}

Listener::~Listener() {}

int	Listener::getSocket() const {
	return _socket;
}