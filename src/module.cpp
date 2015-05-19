#include <boost/python.hpp>
#include "common.hpp"

#include "plugin_wrapper.hpp"
#include "dataaccess_wrapper.hpp"

#include "plugin_docstrings.hpp"
#include "dataaccess_docstrings.hpp"

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

	DEF_FUNCTION(XPLMIsPluginEnabled);
	DEF_FUNCTION(XPLMEnablePlugin);
	DEF_FUNCTION(XPLMDisablePlugin);
	DEF_FUNCTION(XPLMReloadPlugins);

	DEF_FUNCTION(XPLMSendMessageToPlugin);

	SCOPE_ATTR(XPLM_MSG_PLANE_CRASHED);
	SCOPE_ATTR(XPLM_MSG_PLANE_LOADED);
	SCOPE_ATTR(XPLM_MSG_AIRPORT_LOADED);
	SCOPE_ATTR(XPLM_MSG_SCENERY_LOADED);
	SCOPE_ATTR(XPLM_MSG_AIRPLANE_COUNT_CHANGED);
	SCOPE_ATTR(XPLM_MSG_PLANE_UNLOADED);
	SCOPE_ATTR(XPLM_MSG_WILL_WRITE_PREFS);
	SCOPE_ATTR(XPLM_MSG_LIVERY_LOADED);

	DEF_FUNCTION(XPLMHasFeature);
	DEF_FUNCTION(XPLMIsFeatureEnabled);
	DEF_FUNCTION(XPLMEnableFeature);
	def("XPLMEnumerateFeatures", __XPLMEnumerateFeatures, XPLMEnumerateFeatures_doc);

	/***********************************************************************
	 *						XPLMDataRef
	 ***********************************************************************/

	DEF_FUNCTION(XPLMCanWriteDataRef);
	DEF_FUNCTION(XPLMGetDataRefTypes);

}
