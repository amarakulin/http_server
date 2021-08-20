#ifndef TYPEDEF
# define TYPEDEF

# include <map>

typedef std::map<std::string, std::string> requestHeaderStruct;

/*
** Все поля представленны в нижнем регистре
** Обязательно будут заполнены следующие поля:
** - method
** - location
** - protocol
*/

#endif