#ifndef EXCEPTIONS
# define EXCEPTIONS

# include <exception>

class BadRequestException : public std::exception {};
class NotAllowedException : public std::exception {};
class NotFoundException : public std::exception {};

#endif