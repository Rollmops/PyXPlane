#include "plugin_wrapper.hpp"
#include <iostream>

static boost::python::object __retrieveFeature = boost::python::object();
static boost::python::object __inRef = boost::python::object();

#define INFO_BUFFER_SIZE 512

#define NONE_OR_STRING(VAR) (VAR != NULL) ? std::string(VAR) : std::string("")

void retrieveFeature(const char *inFeature, void *inRef)
{
		__retrieveFeature(inFeature, __inRef);
}

void __XPLMEnumerateFeatures(const boost::python::object &inEnumerator, const boost::python::object &inRef)
{
	__retrieveFeature = inEnumerator;
	__inRef = inRef;
	XPLMEnumerateFeatures(retrieveFeature, NULL);
}


boost::python::tuple __XPLMGetPluginInfo(const XPLMPluginID &inPlugin )
{

    char outName[INFO_BUFFER_SIZE];
    char outFilePath[INFO_BUFFER_SIZE];
    char outSignature[INFO_BUFFER_SIZE];
    char outDescription[INFO_BUFFER_SIZE];

    XPLMGetPluginInfo(inPlugin, outName, outFilePath, outSignature, outDescription);

    return boost::python::make_tuple(	NONE_OR_STRING(outName),
    									NONE_OR_STRING(outFilePath),
										NONE_OR_STRING(outSignature),
										NONE_OR_STRING(outDescription));
}


void __XPLMSendMessageToPlugin(const XPLMPluginID &inPlugin, const int &inMessage, const boost::python::object &inParam)
{
	XPLMSendMessageToPlugin(inPlugin, inMessage, PyCapsule_GetPointer(inParam.ptr(), "inParam"));
}

