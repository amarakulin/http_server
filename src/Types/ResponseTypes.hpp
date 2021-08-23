#ifndef RESPONSE_TYPES
# define RESPONSE_TYPES

# include <iostream>

class Response;
class Request;

typedef struct {
	std::string method;
	Response*	(*createResponse)(Request*);
}	ResponseCreatorList;

#endif