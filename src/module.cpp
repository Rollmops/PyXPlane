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
	def("XPLMGetPluginInfo", __XPLMGetPluginInfo, XPLMGetPluginInfo_doc);

	DEF_FUNCTION(XPLMIsPluginEnabled);
	DEF_FUNCTION(XPLMEnablePlugin);
	DEF_FUNCTION(XPLMDisablePlugin);
	DEF_FUNCTION(XPLMReloadPlugins);

	def("XPLMSendMessageToPlugin", __XPLMSendMessageToPlugin, __XPLMSendMessageToPlugin_overloads(args("inPlugin", "inMessage", "inParam"), XPLMSendMessageToPlugin_doc));

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

	def("XPLMEnumerateFeatures", __XPLMEnumerateFeatures, __XPLMEnumerateFeatures_overloads(args("inEnumerator", "inRef"), XPLMEnumerateFeatures_doc));

	/***********************************************************************
	 *						XPLMDataRef
	 ***********************************************************************/

	SCOPE_ATTR(xplmType_Unknown);
	SCOPE_ATTR(xplmType_Int);
	SCOPE_ATTR(xplmType_Float);
	SCOPE_ATTR(xplmType_Double);
	SCOPE_ATTR(xplmType_FloatArray);
	SCOPE_ATTR(xplmType_IntArray);
	SCOPE_ATTR(xplmType_Data);

	def("XPLMFindDataRef", __XPLMFindDataRef, XPLMFindDataRef_doc);
	def("XPLMCanWriteDataRef", __XPLMCanWriteDataRef, XPLMCanWriteDataRef_doc);
	def("XPLMGetDataRefTypes", __XPLMGetDataRefTypes, XPLMGetDataRefTypes_doc);

}
