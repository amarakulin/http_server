#ifndef PARSER_REQUEST
# define PARSER_REQUEST

# include "RequestTypes.hpp"
# include "Exceptions.hpp"
# include "utils.hpp"

# include <iostream>
# include <map>

typedef enum { WITH_CONTENT_LEN, CHUNKED, BOUNDARY } BodyParseType;

static const std::string COMMON_HEADE_DATA[] = {
	"method",
	"uri",//TODO rename to uri
	"protocol",
	""
};

static const std::string SEPORATOR = ": ";
static const std::string END_OF_LINE = "\r\n";
static const std::string END_OF_HEADER = "\r\n\r\n";
static const std::string END_OF_CHUNKED_BODY = "0\r\n\r\n";
static const std::string REQUEST_WITH_BODY = "post put delete";
static const std::string PROCESSED_REQUESTS_LOWER = "get post put delete head";
static const std::string PROCESSED_REQUESTS = "GET POST PUT DELETE HEAD";

class ParserRequest {
	private:
		/*
		** Парсит первую строчку header'а, в которой
		** содержится method, locatian и protocol
		*/
		typedef std::vector<std::string> strVct;
		typedef strVct::iterator		 strVctIt;
		static void	parseCommonHeaderData(std::string& data, requestHeaderStruct& header);
		static void	joinUriPartOfCommonHeaderData(strVctIt start, strVctIt end, strVct& data);
		/*
		** Парсит весь header и заполняет map<std::string, std::string>,
		** где key - имя параметра, а value его значение
		*/
		static void	parseHeaderData(std::string& data, requestHeaderStruct& header);

	public:
		ParserRequest();
		ParserRequest(const ParserRequest& other);
		~ParserRequest();

		/*
		** Функции для определения конца body/header
		** Если условия удовлетворяются, то body/header будет спаршен
		*/

		static bool					handleEndOfHeader(requestHeaderStruct& header, std::string& buffer);

		static bool					handleEndOfBody(RequestData& data, std::string& buffer);
		static bool					handleEndOfBoundaryBody(RequestData& data, std::string& buffer);
		static bool					handleEndOfChunkedBody(RequestData& data, std::string& buffer);
		static bool					handleEndOfBodyWithContentLengt(RequestData& data, std::string& buffer);

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