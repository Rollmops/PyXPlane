#include "dataaccess_wrapper.hpp"

PyObject *__XPLMFindDataRef(const char *inDataRefName)
{
	return PyCapsule_New(XPLMFindDataRef(inDataRefName), "XPLMDataRef", NULL);
}

int __XPLMCanWriteDataRef(PyObject *inDataRef)
{
	return XPLMCanWriteDataRef(PyCapsule_GetPointer(inDataRef, "XPLMDataRef"));
}


XPLMDataTypeID __XPLMGetDataRefTypes(PyObject *inDataRef)
{
	return XPLMGetDataRefTypes(PyCapsule_GetPointer(inDataRef, "XPLMDataRef"));
}
