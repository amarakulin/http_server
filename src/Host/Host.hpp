#ifndef HOST
# define HOST

# include <iostream>

/*
** Класс хранит данные каждого сервера, указанного в config файле
*/

class Host {
	private:
		std::string _ip;
		size_t		_port;
		std::string _hostName;
		// и все необходимые поля
	
	public:
		Host();
		Host(const Host& other);
		Host(std::string ip, size_t port, std::string hostName);

		std::string 	getIp() const;
		size_t			getPort() const;
		std::string		getHostName() const;
};

bool operator==(const Host& lhs, const Host& rhs);

#endif