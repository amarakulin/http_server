#ifndef REQUEST
# define REQUEST

# include "RequestTypes.hpp"
# include "ParserRequest.hpp"

# include <iostream>
# include <sstream>
# include <map>

class Request {
	private:
		int			_status;
		std::string	_buffer;

		RequestData	_data;
		bool		_isHeaderParsed;
		bool		_isBodyParsed;

	public:
		Request();
		Request(const Request& other);
		~Request();

		void	addRequestChunk(std::string chunk);

		bool	isDone();

		void	handleEndOfHeader();
		void	handleEndOfBody();

		void	resetRequest();

		int			getStatus() const;
		RequestData& getData();
		std::string	getMethod();
};

#endif