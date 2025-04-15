#ifndef _initException_
#define _initException_

#include <stdexcept>
#include <string>

class InitException : public std::exception
{
private:
	std::string message;

public:
    InitException(const char* msg) : message(msg) {}

	const char* what() const noexcept
	{
		return message.c_str();
	}
};
#endif
