#ifndef HOSTTYPES
# define HOSTTYPES

# include <iostream>
# include <vector>
// # include <CGI.hpp>

class CGI;

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
	"cgi_extension",
	"cgi_path",
};

/*
*	Структура-дополнение с HostData. Описывает location. Нет обязательных полей.
*/

typedef struct {
	std::string					way;
	std::string					root;
	std::vector<std::string>	httpMethods;
	std::vector<std::string>	index;
	bool						autoindex;
	bool						uploadEnable;
	std::string					uploadPath;
	std::string					cgiExtension; //TODO
	std::string					cgiPath; // TODO
	CGI*						cgi;
	//TODO добавить редирект
} Location;

/*
*	Структура-дополнение к HostData. Описывает ErrorPage.
*/

typedef struct {
	size_t						errorNbr;
	std::string					errorPagePath;
} ErrorPage;

/*
*	Структура со всеми возможными данными из конфигурационного файла. Обязательные поля:
*	- host;
*	- port;
*/

typedef struct {
	std::string					ip;
	std::string					host;
	std::string					serverName;
	size_t						port;
	std::string					root;
	std::vector<ErrorPage*>		errorPage;
	std::string					clientMaxBodySize;
	std::vector<Location*>		location;
} HostData;

#endif