#ifndef HOST
# define HOST

# include <iostream>
# include "HostTypes.hpp"

/*
** Класс хранит данные каждого сервера, указанного в config файле
*/

class Host {
	private:
		HostData	*_data;
		void 		_clone(HostData *hostData);
	
	public:
		Host(HostData *hostData);
		Host(const Host& other);
		Host(std::string ip, size_t port, std::string serverName);
		~Host();

		std::string	getIp() const;
		size_t		getPort() const;
		std::string	getServerName() const;
		std::string	getRoot() const;
		std::string	errorPage() const;
		std::string	getClientMaxBodySize() const;
		HostData* 	getData() const;
};

bool operator==(const Host& lhs, const Host& rhs);

#endif