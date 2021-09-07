#include "ParserConfig.hpp"
#include "Server.hpp"

int main(int argc, char **argv) {
	try {
		Server server(ParserConfig().parse(argv[1]));
		server.start(); 
	} catch(const std::exception& e) {
	}
	return 0;
}