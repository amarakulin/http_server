#ifndef RESPONSE
# define RESPONSE

# include <iostream>

// Здесь понадобиться fork и excve???

class Response {
	protected:
		std::string _head;
		std::string _body;

	public:
		Response();
		Response(const Response& other);
		virtual ~Response();

		virtual std::string createBody();
		std::string 		createHead();

};

#endif