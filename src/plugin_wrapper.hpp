#ifndef _PYXPLANE_PLUGIN_WRAPPER_HPP
#define _PYXPLANE_PLUGIN_WRAPPER_HPP

/*
 * These APIs provide facilities to find and work with other plugins and manage other plugins.
 */

#include <boost/python.hpp>
#include <XPLMPlugin.h>

using namespace boost::python;

void __XPLMEnumerateFeatures(const object &inEnumerator, const object &inRef);


#endif //_PYXPLANE_PLUGIN_WRAPPER_HPP
