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

	std::string uri = header["uri"];
	pos = uri.find('?');
	std::string path_info = (pos == uri.size() ? uri : uri.substr(0, pos));
	env["PATH_INFO"] = path_info;


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

	if (req.header.find("x-secret-header-for-test") != req.header.end()) {
//		std::cout << BOLDRED << "Set secret header env" << RESET << std::endl;
		env["HTTP_X_SECRET_HEADER_FOR_TEST"] = "1";
	}

	return trtansformStringMapToChar(env);
}

char**	CGI::trtansformStringMapToChar(std::map<std::string, std::string> envMap) const {
	char** env =  new char*[envMap.size() * sizeof(char*) + 1];
	int i = 0;

	for (std::map<std::string, std::string>::iterator it = envMap.begin(); it != envMap.end(); i++, it++) {
		env[i] = strdup(((*it).first + "=" + (*it).second).c_str());
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
	int			cgiOut = open("./cgi/cgi_out", O_RDWR | O_TRUNC | O_CREAT, 0777);
	int			cgiReadFrom = open("./cgi/cgi_read_from", O_RDWR | O_TRUNC | O_CREAT, 0777);
	int 		status;

	char **args = new char*[2];
    args[0] = strdup(("." + _pathToCGI).c_str());
    args[1] = NULL;

	write(cgiReadFrom, request.body.c_str(), request.body.length());
	lseek(cgiReadFrom, 0, SEEK_SET);

	if ((pid = fork()) == -1) {
		throw InternalServerErrorException();
		//TODO throw 5** error
	}
	else if (pid == 0)
	{
		dup2(cgiOut, 1);
		dup2(cgiReadFrom, 0);
		if (execve(args[0], args, env) == -1) {
			std::cout << BOLDRED << "Execute CGI error" << RESET << std::endl;
			throw InternalServerErrorException();
			// TODO throw 5** error
		}
		close(cgiOut);
		close(cgiReadFrom);
		exit(1);
	}
	else if (pid > 0) {
		waitpid(pid, &status, 0);

		if (status != 0) {
			std::cout << "Error: status code = " << status << std::endl;
			//TODO 
		}

		body = getDataFileAsString("./cgi/cgi_out");
		body.erase(0, body.find("\r\n\r\n") + 4);
		close(cgiOut);
		close(cgiReadFrom);
	}

	deleteEnv(env);
	delete args[0];
	delete[] args;
	return body;
}
