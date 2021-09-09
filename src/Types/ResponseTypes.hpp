#ifndef RESPONSE_TYPES
# define RESPONSE_TYPES

# include <iostream>

class Response;
class Request;

#define CONTENT_LENGTH "Content-length: "
#define CONTENT_TYPE "Content-type: "
#define LOCATION "Location: "
#define VERSION_HTTP "HTTP/1.1 "
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
	std::string			(*getProcessedHeader)(std::string valueHeader);
}		t_response_process;


#endif