#ifndef PARSER_REQUEST
# define PARSER_REQUEST

# include "RequestTypes.hpp"
// # include "utils.hpp"

# include <iostream>
# include <map>

// class Request;

class ParserRequest {
	public:
		ParserRequest();
		ParserRequest(const ParserRequest& other);
		~ParserRequest();

		requestHeaderStruct	parseHeader(std::string data);
		// Request& parse();
};

#endif

// # include "typedef.hpp"
// # include "utils.hpp"


// static const char* SPLIT_STRING = ": ";
// static const char END_OF_LINE = '\n';

// class Request;

// class ParserRequest {
// 	private:
// 		// void	parseMethod(std::string& data, requestHeaderStruct& header);
// 		// void	parseLocation(std::string& data, requestHeaderStruct& header);
// 		// void	parseProtocol(std::string& data, requestHeaderStruct& header);
	
// 	public:
// 		ParserRequest();
// 		ParserRequest(const ParserRequest& other);
// 		~ParserRequest();

// 		requestHeaderStruct	parseHeader(std::string data);
// 		// Request& parse();
// };
