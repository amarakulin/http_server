#ifndef PARSER_REQUEST
# define PARSER_REQUEST

class Request;

class ParserRequest {
	public:
		ParserRequest();
		Request& parse();
};

#endif