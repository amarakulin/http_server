#ifndef REQUEST
# define REQUEST

# include <iostream>

class Request {
	private:
		std::string _head;
		std::string _body;
		std::string _method;
		size_t		_contentLength;


	public:
		Request();
};

#endif