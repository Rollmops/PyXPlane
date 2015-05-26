#include "dataaccess_wrapper.hpp"

#include <map>

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

static std::map<XPLMDataRef, DataAccessorCallbacks> callbackMap;

REGISTER_GETTER_CALLBACK(int, inReadInt);
REGISTER_GETTER_CALLBACK(float, inReadFloat);
REGISTER_GETTER_CALLBACK(double, inReadDouble);


PyObject *__XPLMRegisterDataAccessor(
                                   const std::string         &inDataName,
                                   XPLMDataTypeID       inDataType,
                                   int                  inIsWritable,
								   boost::python::object       inReadInt,
								   boost::python::object       inWriteInt,
								   boost::python::object       inReadFloat,
								   boost::python::object       inWriteFloat,
								   boost::python::object       inReadDouble,
								   boost::python::object       inWriteDouble,
								   boost::python::object      inReadIntArray,
								   boost::python::object      inWriteIntArray,
								   boost::python::object      inReadFloatArray,
								   boost::python::object      inWriteFloatArray,
								   boost::python::object       inReadData,
								   boost::python::object       inWriteData,
                                   PyObject *               inReadRefcon,
                                   PyObject *               inWriteRefcon)
{
	XPLMDataRef ref = XPLMRegisterDataAccessor(inDataName, inDataType, inIsWritable,
			NULL_OR_CALLBACK(inReadInt),
			NULL_OR_CALLBACK(inWriteInt),
			NULL_OR_CALLBACK(inReadFloat),
			NULL_OR_CALLBACK(inWriteFloat),
			NULL_OR_CALLBACK(inReadDouble),
			NULL_OR_CALLBACK(inWriteDouble),
			NULL_OR_CALLBACK(inReadIntArray),
			NULL_OR_CALLBACK(inWriteIntArray),
			NULL_OR_CALLBACK(inReadFloatArray),
			NULL_OR_CALLBACK(inWriteFloattArray),
			NULL_OR_CALLBACK(inReadData),
			NULL_OR_CALLBACK(inWriteData),
			PyCapsule_GetPointer(inReadRefcon, "XPLMDataRef"),
			PyCapsule_GetPointer(inWriteRefcon, "XPLMDataRef") );

	DataAccessorCallbacks &callbacks = callbackMap[ref];

}
