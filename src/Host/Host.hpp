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
		// и все необходимые поля
	
	public:
		Host();
		Host(std::string ip, size_t port);
};

#endif