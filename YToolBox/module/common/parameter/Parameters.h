#ifndef _BASIC_PARAMETERS_H_
#define _BASIC_PARAMETERS_H_
#include <iostream>
#include <boost/any.hpp>


class Parameters {
public:
	virtual void set(boost::any value) = 0 ;

	virtual std::string get_param_description() = 0;
};	


#endif