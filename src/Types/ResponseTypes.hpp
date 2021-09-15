#ifndef RESPONSE_TYPES
# define RESPONSE_TYPES

# include <iostream>

class Response;
class Request;

#define CONTENT_LENGTH "Content-length: "
#define CONTENT_TYPE "Content-type: "
#define LOCATION "Location: "
#define VERSION_HTTP "HTTP/1.1 "
#define DEFAULT_ERROR_PAGE_PATH "/resources/errorPages/"
#define STATUS_OK 200
#define BAD_REQUEST 400
#define NOT_FOUND 404
#define METHOD_NOT_ALLOWED 405
#define PAYLOAD_TOO_LARGE 413
#define REDIRECT 301
#define INTERNAL_SERVER_ERROR 500
#define NOT_IMPLEMENTED 501
#define BAD_GATE_WAY 502
#define HTTP_NOT_SUPPORTED 505

static const std::pair<int, std::string> arrResponseStatuses [] = {
		std::pair<int, std::string>(200, "OK"),
		std::pair<int, std::string>(301, "Moved Permanently"),
		std::pair<int, std::string>(400, "Bad Request"),
		std::pair<int, std::string>(404, "Not Found"),
		std::pair<int, std::string>(405, "Method Not Allowed"),
		std::pair<int, std::string>(413, "Payload Too Large"),
		std::pair<int, std::string>(500, "Internal Server Error"),
		std::pair<int, std::string>(501, "Not Implemented"),
		std::pair<int, std::string>(502, "Bad Gateway"),
		std::pair<int, std::string>(505, "HTTP Version Not Supported"),


		std::pair<int, std::string>(0, ""),
};
/*
** Структура для автоматического определения наследника класса Response
*/
typedef struct {
	std::string method;
	Response*	(*createResponse)(RequestData&, HostData*);
}	ResponseCreatorList;

/*
** Характеризует текущий статут считывание ответа
*/
typedef enum { NO_RESPONSE, SENDING, SENDED } responseState;

/*
** Структура для автоматического определения обработчика Header
*/
typedef struct {
	const char*		nameHeader;
	std::string			(*getProcessedHeader)(std::string valueHeader, HostData *hostData);
}		t_response_process;


#endif