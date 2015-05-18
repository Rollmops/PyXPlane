#include "plugin_wrapper.hpp"

static python::object __retrieveFeature = python::object();

void retrieveFeature(const char *inFeature, void *inRef)
{
	__retrieveFeature(inFeature, python::object());
}

void __XPLMEnumerateFeatures(const python::object &inEnumerator, const python::object &inRef)
{
	__retrieveFeature = inEnumerator;
	void *_inRef;
	XPLMEnumerateFeatures(retrieveFeature, _inRef);
}
