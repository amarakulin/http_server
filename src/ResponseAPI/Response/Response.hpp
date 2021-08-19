#ifndef RESPONSE
# define RESPONSE

# include <iostream>

// Здесь понадобиться fork и excve???

typedef enum { NO_RESPONSE, SENDING, SENDED } responseStatus;

class Response {
	protected:
		std::string _head;
		std::string _body;

		int			_status;
	
	public:
		Response();
		virtual ~Response();

		virtual std::string createBody();
		std::string 		createHead();
		bool				isResponseSended();
};

#endif