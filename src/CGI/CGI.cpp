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

void	CGI::setIp(const std::string& ip) {
	_ip = ip;
}

void	CGI::setPort(const std::string& port) {
	_port = port;
}

std::string	CGI::getPath() const {
	return _pathToCGI;
}

std::string CGI::getExtension() const {
	return _extension;
}

std::string CGI::getRoot() const {
	return _root;
}

std::string CGI::getIp() const {
	return _ip;
}

std::string CGI::getPort() const {
	return _port;
}