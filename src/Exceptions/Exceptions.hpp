#ifndef EXCEPTIONS
# define EXCEPTIONS

# include <exception>

class BadRequestException : public std::exception {};
class NotAllowedException : public std::exception {};

#endif