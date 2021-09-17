#include "CGI.hpp"

CGI::CGI() {}

CGI::CGI(const std::string& pathToCGI, const std::string& extension,
	const std::string& root, const std::string& ip, const std::string& port) :
	_pathToCGI(pathToCGI), _extension(extension), _root(root), _ip(ip), _port(port) {}

CGI::CGI(const CGI& other) {*this = other;}

CGI::~CGI() {}

void	CGI::createCGIEnv(Request* request, const HostData* hostData) {}