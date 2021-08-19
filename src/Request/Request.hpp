#ifndef REQUEST
# define REQUEST

# include <iostream>

typedef enum { NO_REQUEST, READING, READED } requestStatus;

class Request {
	private:
		std::string _method;
		std::string	_data;
		int			_status;

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