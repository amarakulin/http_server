#include "CGI.hpp"

CGI::CGI() {}

CGI::CGI(const CGI& other) {*this = other;}

CGI::~CGI() {}

void	CGI::createCGIEnv(Request* request, const HostData* hostData) {
	
}

void	CGI::setPath(const std::string& path) {
	_pathToCGI = path;
}

void	CGI::setExtension(const std::string& extension) {
	_extension = extension;
}

void	CGI::setRoot(const std::string& root) {
	_root = root;
}
