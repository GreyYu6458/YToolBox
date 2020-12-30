#ifndef _ILINKABLE_INTERFACE_H_
#define _ILINKABLE_INTERFACE_H_
#include "Interface.h"

class ILinkableInterface: public Interface {
public:
	virtual ~ILinkableInterface(){}
	virtual bool link_to(Interface* interface) = 0;
};

#endif