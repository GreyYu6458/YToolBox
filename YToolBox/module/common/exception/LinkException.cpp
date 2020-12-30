#include "LinkException.h"

LinkException::LinkException(std::string msg) :
	error_msg(std::move(msg)) {
}

char const* LinkException::what() const {
	return error_msg.c_str();
}
