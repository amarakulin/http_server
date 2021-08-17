#include "utils.hpp"

Client& getClientByFD(std::vector<Client> clients, int fd) {
	std::vector<Client>::iterator it = clients.begin();

	for (; it != clients.end(); it++) {
		if ((*it).getSocket() == fd)
			return *it;
	}	
	return *it;
}