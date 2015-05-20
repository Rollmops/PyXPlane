#include "plugin_wrapper.hpp"
#include <iostream>

static boost::python::object __retrieveFeature = boost::python::object();
static boost::python::object __inRef = boost::python::object();


void retrieveFeature(const char *inFeature, void *inRef)
{
		__retrieveFeature(inFeature, __inRef);
}

void __XPLMEnumerateFeatures(const python::object &inEnumerator, const boost::python::object &inRef)
{
	__retrieveFeature = inEnumerator;
	__inRef = inRef;
	XPLMEnumerateFeatures(retrieveFeature, NULL);
}


