#ifndef REQUEST
# define REQUEST

# include <iostream>

typedef enum { NO_REQUEST, READING, READED } requestStatus;

typedef struct {
	std::string method;
	std::string boundary;
	size_t		contentLenght;
	bool		isChunked;
} RequestReadingData;

class Request {
	private:
		int			_status;
		std::string	_data;

		RequestReadingData _sup;

	public:
		Request();
		Request(const Request& other);
		~Request();

		void	addRequestChunk(std::string chunk);
		void	parseMethod();

		bool	isDone();

		void	resetRequest();

		std::string getData() const {
			return _data;
		}
		
		int			getStatus() const;
		std::string	getMethod() const;
};

#endif