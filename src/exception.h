#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>

class Exception: public std::exception
{
private:
    const char * message = nullptr;
public:
    Exception() = delete;
    explicit Exception(const char * s) throw() : message(s) {}
    const char * what() const throw() { return message; }
};

#endif // _EXCEPTION_H
