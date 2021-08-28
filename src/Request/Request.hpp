#ifndef REQUEST
# define REQUEST

//# include "RequestTypes.hpp"
# include "ParserRequest.hpp"

//FOR Debug for lovely Clion
#include "../Types/RequestTypes.hpp"

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

		void		addRequestChunk(std::string chunk);
		void		resetRequest();

		bool		isDone();

		int			getStatus() const;
		RequestData& getData();
		std::string	getMethod();
};

#endif