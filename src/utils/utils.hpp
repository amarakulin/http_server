#ifndef UTILS
# define UTILS

# include "Client.hpp"
# include <vector>

Client getClientByFD(std::vector<Client> clients, int fd);

#endif