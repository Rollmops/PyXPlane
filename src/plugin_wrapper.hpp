#ifndef _PYXPLANE_PLUGIN_WRAPPER_HPP
#define _PYXPLANE_PLUGIN_WRAPPER_HPP

/*
 * These APIs provide facilities to find and work with other plugins and manage other plugins.
 */

#include <boost/python.hpp>
#include <boost/function.hpp>
#include <XPLMPlugin.h>

using namespace boost;

void __XPLMEnumerateFeatures(const python::object &inEnumerator, const python::object &inRef);


#endif //_PYXPLANE_PLUGIN_WRAPPER_HPP
