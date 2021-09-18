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
	// 127.0.0.1:8000/cgi-bin/hello.pl/index.html?a=1&b=2 => index.html
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
	std::string response;
	int			FD[2];
	int			s;

	pipe(FD);
	fcntl(FD[0], F_SETFL, fcntl(FD[0], F_GETFL) | O_NONBLOCK);
	fcntl(FD[1], F_SETFL, fcntl(FD[1], F_GETFL) | O_NONBLOCK);

	int status;

	char **args = new char*[2];
    args[0] = strdup(("." + _pathToCGI).c_str());
    args[1] = NULL;

	if ((pid = fork()) == -1) {
		//TODO throw 5** error
	}
	else if (pid == 0)
	{
		dup2(FD[1], 1);
		dup2(FD[0], 0);
		if (execve(args[0], args, env) == -1) {
			// TODO throw 5** error
		}
		close(FD[0]);
		close(FD[1]);
		exit(1);
	}
	else if (pid > 0) {
		dup2(FD[0], 0);
		std::cout << request.body << std::endl;
		write(FD[1], request.body.c_str(), request.body.length());
		waitpid(pid, &status, 0);
		close(FD[1]);

		if (status != 0) {
			std::cout << "Error: status code = " << status << std::endl;
			//TODO 
		}


		size_t size = 1500;
		char buf[size];
		bzero(buf, size);
		while ((s = read(FD[0], buf, size)) > 0) {
			// std::cout << "Readed: " << s << std::endl;
			// std::cout << "s: " << s << std::endl;
			// std::cout << "Buff: " << strlen(buf) << std::endl;
			response += buf;
			bzero(buf, size);
		}
		close(FD[0]);
	}

	deleteEnv(env);
	delete args[0];
	delete[] args;
	size_t pos = 0;
	// pos = response.find("\r\n\r\n") + 4;
	// std::string body = response.substr(pos);
	// std::string header = response.substr(0, pos);
	// // std::cout << "Body:" << body << std::endl;
	// std::cout << "Response:" << std::endl << response;
	// std::cout << std::endl << "Len: " << response.length() << std::endl;
	// std::cout << std::endl << "Header len: " << header.length() << std::endl;
	std::cout << response.substr(response.find("\r\n\r\n") + 4) << std::endl;
	return response.substr(response.find("\r\n\r\n") + 4);
}
