#include <boost/python.hpp>
#include "common.hpp"

#include "plugin_wrapper.hpp"
#include "docstrings.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(api)
{
	scope().attr("__version__") = std::string(xstr(__EXTENSION_VERSION__));

	/***********************************************************************
	 *						XPLMPlugin
	 ***********************************************************************/

	DEF_FUNCTION(XPLMGetMyID);
	DEF_FUNCTION(XPLMCountPlugins);
	DEF_FUNCTION(XPLMGetNthPlugin);
	DEF_FUNCTION(XPLMFindPluginByPath);
	DEF_FUNCTION(XPLMFindPluginBySignature);
	DEF_FUNCTION(XPLMGetPluginInfo);
}
