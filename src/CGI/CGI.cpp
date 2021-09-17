#include "CGI.hpp"

CGI::CGI() {}

CGI::CGI(const std::string& pathToCGI, const std::string& extension,
	const std::string& root, const std::string& ip, const std::string& port) :
	_pathToCGI(pathToCGI), _extension(extension), _root(root), _ip(ip), _port(port) {}

CGI::CGI(const CGI& other) {*this = other;}

CGI::~CGI() {}

char**	CGI::createCGIEnv(RequestData& req) const {
	std::string								body = req.body;
	requestHeaderStruct						header = req.header;
	requestHeaderStruct::iterator			endOfHeader = header.end();
	std::map<std::string, std::string> 		env;
	size_t									pos = 0;
	size_t									substrLen = 0;

	if (header.find("content-length") != endOfHeader) {
		env["CONTENT_LENGTH"] = header["content-length"];
	}

	if (header.find("content-type") != endOfHeader) {
		env["CONTENT_TYPE"] = header["content-type"];
	}

	env["GATEWAY_INTERFACE"] = "CGI/1.1";

	// 127.0.0.1:8000/cgi-bin/hello.pl/index.html?a=1&b=2 => index.html
	// env["PATH_INFO"] = ""; //TODO


	env["REQUEST_METHOD"] = header["method"];
	std::string protocol = header["protocol"];
	toUpperCase(protocol);
	env["SERVER_PROTOCOL"] = protocol;

	pos = header["uri"].rfind('?');
	env["DOCUMENT_URI"] = pos == std::string::npos ? header["uri"] : header["uri"].substr(0, pos);
	env["REQUEST_URI"] = header["uri"];
	env["QUERY_STRING"] = pos == std::string::npos ? "" : header["uri"].substr(pos, header["uri"].length() - pos);

	pos = _pathToCGI.rfind("/");
	substrLen = _pathToCGI.length() - pos;
	if (pos + 1 == _pathToCGI.length()) {
		pos = _pathToCGI.rfind("/", pos - 2);
		substrLen = _pathToCGI.length() - pos - 1;
	}

	env["SCRIPT_NAME"] = pos == std::string::npos ? _pathToCGI : _pathToCGI.substr(pos, substrLen);
	env["SCRIPT_FILENAME"] = _root + _pathToCGI;

	env["DOCUMENT_ROOT"] = _root;

	env["SERVER_NAME"] = _ip;
	env["SERVER_PORT"] = _port;
	env["SERVER_SOFTWARE"] = "http_server/1.0.0";

	for (std::map<std::string, std::string>::iterator i = env.begin(); i != env.end(); i++) {
		std::cout << (*i).first << ": " << (*i).second << std::endl;
	}

	return trtansformStringMapToChar(env);
}

char**	CGI::trtansformStringMapToChar(std::map<std::string, std::string> envMap) const {
	char** env =  new char*[envMap.size() * sizeof(char*) + 1];
	int i = 0;

	for (std::map<std::string, std::string>::iterator it = envMap.begin(); it != envMap.end(); i++, it++) {
		env[i] = strdup(((*it).first + "=" + (*it).second).c_str());
		std::cout << env[i] << std::endl;
	}
	env[i] = NULL;

	return env;
}

void	CGI::deleteEnv(char** env) const {
	if (env) {
		for (int i = 0; env[i] != NULL; i++) {
			delete env[i];
		}
		delete[] env;
	}
	env = NULL;
}

std::string	CGI::execute(RequestData& request) const {
	char**		env = createCGIEnv(request);
	pid_t		pid;
	std::string body;

	pid = fork();
	switch (pid) {
		case -1:
			//TODO throw 5** error
		case 0:
			if (execve(_pathToCGI.c_str(), NULL, env) == -1) {
				// TODO throw 5** error
			}
			std::cout << "After EXECVE" << std::endl;
			exit(0);
		default:
			wait(NULL);
	}
	
	deleteEnv(env);
	return body;
}
