#ifndef REQUEST
# define REQUEST

# include <iostream>
# include <sstream>
# include <map>

typedef enum { NO_REQUEST, READING, READED } requestStatus;

typedef struct {
	std::map<std::string, std::string> 	header;
	std::string							body;
}	RequestData;

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

		void	resetRequest();

		int			getStatus() const;
		RequestData& getData();
		std::string	getMethod();
};

#endif