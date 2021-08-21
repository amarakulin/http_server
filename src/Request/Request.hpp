#ifndef REQUEST
# define REQUEST

# include "RequestTypes.hpp"
# include "ParserRequest.hpp"

# include <iostream>
# include <sstream>
# include <map>

static const std::string END_OF_HEADER = "\r\n\r\n";

class Request {
	private:
		int			_status;
		std::string	_buffer;

		RequestData	_data;

	public:
		Request();
		Request(const Request& other);
		~Request();

		void	addRequestChunk(std::string chunk);

		bool	isDone();

		void	handleEndOfHeader();

		void	resetRequest();

		int			getStatus() const;
		RequestData& getData();
		std::string	getMethod();
};

#endif