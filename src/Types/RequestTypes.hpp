#ifndef REQUEST_TYPES
# define REQUEST_TYPES

# include <map>
# include <iostream>

typedef std::map<std::string, std::string> requestHeaderStruct;

/*
** Все поля представленны в нижнем регистре
** Обязательно будут заполнены следующие поля:
** - method
** - location
** - protocol
*/

typedef enum { NO_REQUEST, READING, READED } requestStatus;

/*
** Характеризует текущий статут считывание запроса
*/

typedef struct {
	requestHeaderStruct header;
	std::string			body;
}	RequestData;

/*
** Структура для хранения данных запроса
*/

#endif