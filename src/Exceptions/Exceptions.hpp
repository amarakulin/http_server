#ifndef EXCEPTIONS
# define EXCEPTIONS

# include <exception>

class BadRequestException : public std::exception {};

#endif