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
static const std::string END_OF_HEADER = "\r\n\r\n";

class ParserRequest {
	private:
		/*
		** Парсит первую строчку header'а, в которой
		** содержится method, locatian и protocol
		*/
		static void	parseCommonHeaderData(std::string& data, requestHeaderStruct& header);
		/*
		** Парсит весь header и заполняет map<std::string, std::string>,
		** где key - имя параметра, а value его значение
		*/
		static void	parseHeaderData(std::string& data, requestHeaderStruct& header);

	public:
		ParserRequest();
		ParserRequest(const ParserRequest& other);
		~ParserRequest();

		static requestHeaderStruct	parseHeader(std::string data);

		/*
		** Cunked
		*/
		static std::string			parseBody(std::string& data);
		/*
		** With content-length
		*/
		static std::string			parseBody(std::string& data, int contentLengt);
		/*
		** Boundary: 
		** Парсит только ту часть body, в котором есть поле filename
		*/
		static std::string			parseBody(std::string& data, int contentLengt, std::string boundary);
		static std::string			parseBoundaryChunk(std::string& chunk);
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
