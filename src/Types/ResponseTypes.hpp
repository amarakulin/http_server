#ifndef RESPONSE_TYPES
# define RESPONSE_TYPES

# include <iostream>

class Response;
class Request;

typedef struct {
	std::string method;
	Response*	(*createResponse)(Request*);
}	ResponseCreatorList;

typedef enum { NO_RESPONSE, SENDING, SENDED } responseState;

typedef struct {
	const char*		name;
	const int		number;
}		response_status;

/*
** Характеризует текущий статут считывание ответа
*/

#endif