#ifndef CGI_HPP
# define CGI_HPP

# include <iostream>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <map>
# include "RequestTypes.hpp"
# include "utils.hpp"
# include "Exceptions.hpp"
# include "fstream"

# define STD_IN 0
# define STD_OUT 1

/*
** CONTENT_LENGTH 						// Content-length из запроса или -1, если в запросее нет body //!
** CONTENT_TYPE							// Содержит тип файла, возвращаемого запросом //!
** GATEWAY_INTERFACE					// Устанавливает версию CGI //!
** PATH_INFO							// Cодержит дополнительную информацию, которая отображается после имени CGI-скрипта.
** PATH_TRANSLATED						// Содержит фактический физический путь до запрашиваемого файла //? root + PATH_INFO
** QUERY_STRING							// Содержит информацию о запросе добавляется к URL-адресу после знака вопроса //!
** REMOTE_ADDR							// Указывает IP-адрес клиентского компьютера, отправляющего запрос
** REQUEST_METHOD						// Содержит метод запроса //!
** REQUEST_URI							// Сожержит URI запроса //!
** DOCUMENT_URI							// Сожержит URI запроса без Query параметров //!
** DOCUMENT_ROOT						// Сожержит физический путь к корню //!
** SCRIPT_NAME							// Содержит виртуальный путь к скрипту //!
** SCRIPT_FILENAME						// Содержит фактический физический путь до скрипта //!
** SERVER_NAME							// Содержит имя сервера (доменное имя/IP ) //!
** SERVER_PORT							// Порт, который прослушивает сервер //!
** SERVER_PROTOCOL						// Содержит протокол, по которому был передан запрос //!
** SERVER_SOFTWARE						// Содержит имя и версию программного обеспечения, запущенного на веб-сервере (webserver 1.0.0) //!
** HTTP_X_SECRET_HEADER_FOR_TEST
*/

// http://lemp.test/test.php/foo/bar.php?v=1
// 'SCRIPT_FILENAME' => '/var/www/test.php',
// 'SCRIPT_NAME' => '/test.php',

class CGI {
	private:

		char** 	trtansformStringMapToChar(std::map<std::string, std::string> envMap) const;
		char**	createCGIEnv(RequestData& request) const;

		void	deleteEnv(char** env) const;
		

	public:
		std::string _pathToCGI;
		std::string _extension;
		std::string	_root;
		std::string _ip;
		std::string	_port;
		CGI();
		CGI(const std::string& pathToCGI, const std::string& extension,
			const std::string& root, const std::string& ip, const std::string& port);
		CGI(const CGI& other);
		~CGI();

		std::string	execute(RequestData& request) const;
};

#endif