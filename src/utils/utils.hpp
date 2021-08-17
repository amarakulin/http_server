#ifndef UTILS
# define UTILS

# include "Client.hpp"
# include <vector>

Client findClientByFD(std::vector<Client> clients, int fd);

#endif