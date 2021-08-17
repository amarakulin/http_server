#include "utils.hpp"

Client findClientByFD(std::vector<Client> clients, int fd) {
	std::vector<Client>::iterator it = clients.begin();

	for (; (*it).getSocket() == fd && it != clients.end(); it++) ;	
	return *it;
}