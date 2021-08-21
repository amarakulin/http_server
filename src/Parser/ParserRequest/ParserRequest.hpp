#ifndef PARSER_REQUEST
# define PARSER_REQUEST

# include "RequestTypes.hpp"
# include "utils.hpp"

# include <iostream>
# include <map>

typedef enum { WITH_CONTENT_LEN, CHUNKED, BOUNDARY } BodyParseType;

static const std::string COMMON_HEADE_DATA[] = {
	"method",
	"location",
	"protocol",
	""
};

static const std::string SEPORATOR = ": ";
static const std::string END_OF_LINE = "\r\n";

class ParserRequest {
	private:
		/*
		** Парсит первую строчку header'а, в которой
		** содержится method, locatian и protocol
		*/
		static void	parseCommonHeaderData(std::string& data, requestHeaderStruct& header);
		static void	parseHeaderData(std::string& data, requestHeaderStruct& header);

	private:
		static void	parseBodyWithContentLength(std::string& data, std::string& body);
		static void	parseBodyBoundary(std::string& data, std::string& body);
		static void	parseBodyChunked(std::string& data, std::string& body);
	
	public:
		ParserRequest();
		ParserRequest(const ParserRequest& other);
		~ParserRequest();

		static requestHeaderStruct	parseHeader(std::string data);
		static std::string			parseBody(std::string& data, int type);
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
