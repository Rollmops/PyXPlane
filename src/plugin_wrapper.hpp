#ifndef _PYXPLANE_PLUGIN_WRAPPER_HPP
#define _PYXPLANE_PLUGIN_WRAPPER_HPP

/*
 * These APIs provide facilities to find and work with other plugins and manage other plugins.
 */

#include <boost/python.hpp>
#include <boost/function.hpp>
#include <XPLMPlugin.h>

boost::python::tuple __XPLMGetPluginInfo(const XPLMPluginID &inPlugin );

void __XPLMEnumerateFeatures(const boost::python::object &inEnumerator, const boost::python::object &inRef = boost::python::object());
BOOST_PYTHON_FUNCTION_OVERLOADS(__XPLMEnumerateFeatures_overloads, __XPLMEnumerateFeatures, 1, 2);

#endif //_PYXPLANE_PLUGIN_WRAPPER_HPP
