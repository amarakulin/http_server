#include "CGI.hpp"

CGI::CGI(const std::string& path,
			const std::string& extension,
			const std::string& root) : _pathToCGI(path) {}

CGI::CGI(const CGI& other) {*this = other;}

CGI::~CGI() {}

void	CGI::createCGIEnv(Request* request, const HostData* hostData) {
	
}
