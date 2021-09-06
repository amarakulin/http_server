#ifndef HOST
# define HOST

# include <iostream>
# include "HostTypes.hpp"

/*
** Класс хранит данные каждого сервера, указанного в config файле
*/

class Host {
	private:
		HostData _data;
	
	public:
		Host();
		Host(const Host& other);
		Host(std::string ip, size_t port, std::string hostName);


		std::string	getIp() const;
		size_t		getPort() const;
		std::string	getHostName() const;
		std::string	getRoot() const;
		std::string	errorPage() const;
		std::string	getClientMaxBodySize() const;
};

bool operator==(const Host& lhs, const Host& rhs);

#endif