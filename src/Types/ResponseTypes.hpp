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

#define INTERNAL_SERVER_ERROR 500
#define NOT_IMPLEMENTED 501
#define BAD_GATE_WAY 502
#define HTTP_NOT_SUPPORTED 505


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