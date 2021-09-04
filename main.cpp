#include "ParserConfig.hpp"
#include "Server.hpp"

int main(int , char** argv) {
	Server server(ParserConfig().parse(argv[1]));
	// ParserConfig().parse(argv[1]);
	server.start(); 
	return 0;
}