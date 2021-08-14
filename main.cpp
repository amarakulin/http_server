#include "ParserConfig.hpp"
#include "Server.hpp"

int main(int , char** argv) {
	Server server(ParserConfig().parse(argv));
	server.start();
	return 0;
}