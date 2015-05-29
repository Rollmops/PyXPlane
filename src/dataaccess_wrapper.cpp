#include "dataaccess_wrapper.hpp"

#include <map>

PyObject *__XPLMFindDataRef(const char *inDataRefName)
{
	XPLMDataRef dataRef = XPLMFindDataRef(inDataRefName);
	std::cout << "find: " << dataRef << std::endl;
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
	std::cout << "before pycapsule" << std::endl;
	XPLMDataRef _inDataRef = PyCapsule_GetPointer(inDataRef, "XPLMDataRef");
	std::cout << "after pycapsule" << std::endl;

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

DEFINE_GETTER_CALLBACK(inReadInt, int);
DEFINE_GETTER_CALLBACK(inReadFloat, float);
DEFINE_GETTER_CALLBACK(inReadDouble, double);

#define NONE_TO_NULL(NAME) NAME == boost::python::object() ? NULL : NAME ## _callback

PyObject *__XPLMRegisterDataAccessor(
                                   const char *inDataName,
                                   XPLMDataTypeID       inDataType,
                                   int                  inIsWritable,
								   const boost::python::object &inReadInt,
								   const boost::python::object &inWriteInt,
								   const boost::python::object &inReadFloat,
								   const boost::python::object &inWriteFloat,
								   const boost::python::object &inReadDouble,
								   const boost::python::object &inWriteDouble,
								   const boost::python::object &inReadIntArray,
								   const boost::python::object &inWriteIntArray,
								   const boost::python::object &inReadFloatArray,
								   const boost::python::object &inWriteFloatArray,
								   const boost::python::object &inReadData,
								   const boost::python::object &inWriteData,
                                   const boost::python::object	&inReadRefCon,
								   const boost::python::object	&inWriteRefCon
								   )
{
	void *inReadRefConPtr = NULL;
	void *inWriteRefConPtr = NULL;
//	if( inReadRefCon.ptr() != Py_None ) {
//		std::cout << boost::python::extract<const char*>(inReadRefCon) << std::endl;
//		inReadRefConPtr = PyCapsule_GetPointer(inReadRefCon.ptr(), "XPLMDataRef");
//	}
//	if( inWriteRefCon.ptr() != Py_None ) {
//		std::cout << boost::python::extract<const char*>(inWriteRefCon) << std::endl;
//		inWriteRefConPtr = PyCapsule_GetPointer(inWriteRefCon.ptr(), "XPLMDataRef");
//	}

	XPLMDataRef ref = XPLMRegisterDataAccessor(inDataName, inDataType, inIsWritable,
			NONE_TO_NULL(inReadInt), NULL,
			NONE_TO_NULL(inReadFloat), NULL,
			NONE_TO_NULL(inReadDouble), NULL,
			NULL, NULL,
			NULL, NULL,
			NULL, NULL,
			inReadRefConPtr,
			inWriteRefConPtr);

	DataAccessorCallbacks &callbacks = callbackMap[ref];
	callbacks.inReadInt = inReadInt;
	callbacks.inReadFloat = inReadFloat;
	callbacks.inReadDouble = inReadDouble;

	PyObject *ret = PyCapsule_New(ref, inDataName, NULL);
	return ret;
}
