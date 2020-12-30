#include "BasicModule.h"
#include "interface/Interface.h"
#include "interface/ILinkableInterface.h"
#include "exception/LinkException.h"
#include "boost/dll/import.hpp"

/*
int module_link(BasicModule* m_module, const std::string& m_interface_name,
	BasicModule* c_module, const std::string& c_interface_name) {
	auto m_interface_ptr = m_module->getInterface(m_interface_name);
	auto c_interface_ptr = c_module->getInterface(c_interface_name);
	if ( m_interface_ptr == nullptr)
		throw LinkException("Module has no interface named:" + m_interface_name);
	if ( c_interface_ptr == nullptr)
		throw LinkException("Module has no interface named:" + c_interface_name);
	if (m_interface_ptr->getInterfaceDirection() != Interface::OUTPUT ||
		c_interface_ptr->getInterfaceDirection() != Interface::INPUT)
		throw LinkException("Interface direction error");
	if (!dynamic_cast<ILinkableInterface*>(m_interface_ptr)->link_to(c_interface_ptr))
		throw LinkException("Different type between interfaces");
}
*/

/*
 std::shared_ptr<BasicModule> get_module(const boost::dll::shared_library& lib) {
	 auto creator = boost::dll::import_alias<std::shared_ptr<BasicModule>()>
		(lib, "create_plugin");
	 return std::move(creator());
}
*/