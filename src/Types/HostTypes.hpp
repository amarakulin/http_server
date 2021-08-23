#ifndef HOSTTYPES_HPP
# define HOSTTYPES_HPP

# include <iostream>
# include <vector>

// # define GET_VARIABLE_NAME(var) (#var)

static const int SIZE_OF_KEYS = 6;
static const int SIZE_OF_LOCATION_KEYS = 8;

static const std::string keys[SIZE_OF_KEYS] = {
	"listen",
	"server_name",
	"root",
	"error_page",
	"client_max_body_size"
	"location",
};

static const std::string locationKeys[SIZE_OF_LOCATION_KEYS] = {
	"root",
	"methods",
	"autoindex",
	"index",
	"upload_enable",
	"upload_path",
	"cgi_extencion",
	"cgi_path",
};

/*
** Структура-дополнение с HostData. Нет обязательных полей.
*/

typedef struct {
	std::string					way;
	std::string					root;
	std::vector<std::string>	httpMethods;
	std::vector<std::string>	index;
	bool						autoindex;
	bool						uploadEnable;
	std::string					uploadPath;
	std::string					cgiExtencion;
	std::string					cgiPath;
} Location;

/*
** Структура со всеми возможными данными из конфигурационного файла. Обязательные поля:
** - host;
** - port;
** - errorPage;
** - location;
*/

typedef struct {
	std::string					ip;
	std::string					host;
	size_t						port;
	std::string					root;
	std::string					errorPage;
	std::string					clientMaxBodySize;
	std::vector<Location>		location;
} HostData;

#endif