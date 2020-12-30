#ifndef _LINK_EXCEPTION_H_
#define _LINK_EXCEPTION_H_
#include <iostream>


class LinkException : public std::exception {
public:
	LinkException(std::string msg);

	virtual char const* what() const;
private:
	std::string error_msg;
};


#endif