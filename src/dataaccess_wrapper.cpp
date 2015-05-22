#include "dataaccess_wrapper.hpp"

PyObject *__XPLMFindDataRef(const char *inDataRefName)
{
	XPLMDataRef dataRef = XPLMFindDataRef(inDataRefName);
	if (dataRef != NULL ) {
		return PyCapsule_New(dataRef, "XPLMDataRef", NULL);
	} else {
		Py_RETURN_NONE;
	}
}

int __XPLMCanWriteDataRef(PyObject *inDataRef)
{
	return XPLMCanWriteDataRef(PyCapsule_GetPointer(inDataRef, "XPLMDataRef"));
}


XPLMDataTypeID __XPLMGetDataRefTypes(PyObject *inDataRef)
{
	return XPLMGetDataRefTypes(PyCapsule_GetPointer(inDataRef, "XPLMDataRef"));
}

GET_DATA(int, i);
GET_DATA(float, f);
GET_DATA(double, d);

SET_DATA(int, i);
SET_DATA(float, f);
SET_DATA(double, d);

GET_DATA_VECTOR(int, i);
GET_DATA_VECTOR(float, f);

std::string __XPLMGetDatab(PyObject *inDataRef, int inOffset, int inMax )
{
	void *outValues;
	XPLMDataRef _inDataRef = PyCapsule_GetPointer(inDataRef, "XPLMDataRef");

	if( inMax == -1 ) {
		inMax = XPLMGetDatab (_inDataRef, NULL, 0, 0);
	}
	XPLMGetDatab (_inDataRef, outValues, inOffset, inMax);
	return std::string((const char*)outValues, inMax);
}

SET_DATA_VECTOR(int, i);
SET_DATA_VECTOR(float, f);

void __XPLMSetDatab(PyObject *inDataRef, const char *inValue, int inOffset, int inMax )
{
	const int _inMax = inMax == -1 ? strlen(inValue) : inMax;
	XPLMSetDatab(PyCapsule_GetPointer(inDataRef, "XPLMDataRef"), (void*)inValue, inOffset, _inMax);
}
