#ifndef REQUEST
# define REQUEST

# include <iostream>

typedef enum { NO_REQUEST, READING, DONE } requestStatus;

class Request {
	private:
		std::string _head;
		std::string _body;
		std::string _method;
//		size_t		_contentLength;

		std::string	_data;
		int			_status;

	public:
		Request();
		Request(const Request& other);
		~Request();
		Request* clone() const;

		void	addRequestChunk(std::string chunk);

		// int		getStatus() const;
		bool	isDone();

		void	resetRequest();

		std::string getData() const {
			return _data;
		}
		
		int		getStatus() const;
};

#endif