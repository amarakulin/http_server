#ifndef PARSER_REQUEST
# define PARSER_REQUEST

# include "typedef.hpp"

# include <iostream>
# include <map>

class Request;

class ParserRequest {
	public:
		ParserRequest();
		ParserRequest(const ParserRequest& other);
		~ParserRequest();

		requestHeaderStruct	parseHeader(std::string data);
		Request& parse();
};

#endif