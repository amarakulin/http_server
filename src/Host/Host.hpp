#ifndef HOST
# define HOST

# include <iostream>
# include <vector>

/*
** Класс хранит данные каждого сервера, указанного в config файле
*/

typedef struct {
	std::string way;
	std::string root;
	std::vector<std::string> httpMethods;
	std::vector<std::string> index;
	bool autoindex;
	bool uploadEnable;
	std::string uploadPath;
	std::string cgiExtencion;
	std::string cgiPath;
} Location;

typedef struct {
	std::string ip;
	std::string host;
	size_t 		port;
	std::string root;
	std::string errorPage;
	std::string clientMaxBodySize;
	Location location;
} HostData;

class Host {
	private:
		HostData _data;
		// std::string _ip;
		// size_t		_port;
		// std::string _hostName;
		// и все необходимые поля
	
	public:
		Host();
		Host(std::string ip, size_t port, std::string hostName);

		std::string 	getIp() const;
		size_t			getPort() const;
		std::string		getHostName() const;
};

bool operator==(const Host& lhs, const Host& rhs);

#endif