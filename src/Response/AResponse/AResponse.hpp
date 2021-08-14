#ifndef ARESPONSE
# define ARESPONSE

# include <iostream>

// Здесь понадобиться fork и excve???

class AResponse {
	protected:
		std::string _head;
		std::string _body;
	
	public:
		AResponse();
		virtual ~AResponse();

		virtual std::string createBody() = 0;
		std::string 		createHead();
};

#endif