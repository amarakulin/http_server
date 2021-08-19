#ifndef RESPONSE
# define RESPONSE

# include <iostream>

// Здесь понадобиться fork и excve???

typedef struct {
	std::string	head;
	std::string	body;
}	ResponseData;

class Response {
	protected:
		ResponseData _data;

		size_t		_sendedData;
		size_t		_leftDataToSend;

	public:
		Response();
		Response(const Response& other);
		virtual ~Response();

		virtual std::string createBody();
		std::string 		createHead();

};

#endif