#ifndef REQUEST
# define REQUEST

# include <iostream>

typedef enum { READING, DONE } requestStatus; //! DELETE

class Request {
	private:
		std::string _head;
		std::string _body;
		std::string _method;
//		size_t		_contentLength;

		std::string	_data;
//		int			_status;//! DELETE

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
};

#endif