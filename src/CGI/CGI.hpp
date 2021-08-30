#ifndef CGI_HPP
# define CGI_HPP

# include <iostream>
# include "Request.hpp"

/*
** CONTENT_LENGTH 						// Content-length из запроса или -1, если в запросее нет body
** CONTENT_TYPE							// Содержит тип файла, возвращаемого запросом
** GATEWAY_INTERFACE					// Устанавливает версию CGI
** PATH_INFO							// Солнительную информацию, которая отображается после имени CGI-скрипта.
** PATH_TRANSLATED						// Содержит фактический физический путь до запрашиваемого файла 
** QUERY_STRING							// Содержит информацию о запросе добавляется к URL-адресу после знака вопроса
** REMOTE_ADDR							// Указывает IP-адрес клиентского компьютера, отправляющего запрос
** REQUEST_METHOD						// Содержит метод запроса
** REQUEST_URI							// Сожержит URI запроса
** SCRIPT_NAME							// Содержит виртуальный путь к скрипту
** SCRIPT_FILENAME						// Содержит фактический физический путь до скрипта
** SERVER_NAME							// Содержит имя сервера (доменное имя)
** SERVER_PORT							// Порт, который прослушивает сервер
** SERVER_PROTOCOL						// Содержит протокол, по которому был передан запрос
** SERVER_SOFTWARE						// Содержит имя и версию программного обеспечения, запущенного на веб-сервере (webserver 1.0.0)
** HTTP_X_SECRET_HEADER_FOR_TEST
*/

// http://lemp.test/test.php/foo/bar.php?v=1
// 'SCRIPT_FILENAME' => '/var/www/test.php',
// 'SCRIPT_NAME' => '/test.php',

class CGI {
	private:
		std::string _pathToCGI;
		CGI();

	public:
		CGI(const std::string& path);
		CGI(const CGI& other);
		~CGI();

		void	createCGIEnv(const Request& request);
};

#endif