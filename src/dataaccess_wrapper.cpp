#include "dataaccess_wrapper.hpp"
#include <map>
#include <stdlib.h>

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
GET_DATA(double, f);
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

static std::map<void *, DataAccessorCallbacksStruct> callbackMap;
static std::map<void *, boost::python::object> refConReadMap;
static std::map<void *, boost::python::object> refConWriteMap;

READ_CALLBACK(inReadInt, int);
READ_CALLBACK(inReadFloat, float);
READ_CALLBACK(inReadDouble, double);

WRITE_CALLBACK(inWriteInt, int);
WRITE_CALLBACK(inWriteFloat, float);
WRITE_CALLBACK(inWriteDouble, double);

READ_ARRAY_CALLBACK(inReadIntArray, int);
READ_ARRAY_CALLBACK(inReadFloatArray, float);

WRITE_ARRAY_CALLBACK(inWriteIntArray, int);
WRITE_ARRAY_CALLBACK(inWriteFloatArray, float);

PyObject *__XPLMRegisterDataAccessor(
									const char *inDataName,
									const XPLMDataTypeID &inDataType,
									const int &inIsWritable,
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
									const boost::python::object &inReadRefCon,
									const boost::python::object &inWriteRefCon
								   )
{
	if (inReadFloat.ptr() != Py_None ) {
		std::cerr << "!! Warning: It is not recommended to use the float callback read in XPLMRegisterDataAccessor function !!" << std::endl;
	}
	void* indexPtr = (void*)inDataName;

	refConReadMap[indexPtr] = inReadRefCon;
	refConWriteMap[indexPtr] = inWriteRefCon;
	DataAccessorCallbacksStruct &callbacks = callbackMap[indexPtr];

	XPLMDataRef ref = XPLMRegisterDataAccessor(inDataName, inDataType, inIsWritable,
			NONE_TO_NULL(inReadInt), NONE_TO_NULL(inWriteInt),
			NONE_TO_NULL(inReadFloat), NONE_TO_NULL(inWriteFloat),
			NONE_TO_NULL(inReadDouble), NONE_TO_NULL(inWriteDouble),
			NONE_TO_NULL(inReadIntArray), NONE_TO_NULL(inWriteIntArray),
			NONE_TO_NULL(inReadFloatArray), NONE_TO_NULL(inWriteFloatArray),
			NULL, NULL,
			indexPtr,
			indexPtr);

	callbacks.inReadInt = inReadInt;
	callbacks.inWriteInt = inWriteInt;
	callbacks.inReadFloat = inReadFloat;
	callbacks.inWriteFloat = inWriteFloat;
	callbacks.inReadDouble = inReadDouble;
	callbacks.inWriteDouble = inWriteDouble;
	callbacks.inReadIntArray = inReadIntArray;
	callbacks.inReadFloatArray = inReadFloatArray;
	callbacks.inWriteIntArray = inWriteIntArray;
	callbacks.inWriteFloatArray = inWriteFloatArray;

	PyObject *ret = PyCapsule_New(ref, "XPLMDataRef", NULL);
	return ret;
}

void __XPLMUnregisterDataAccessor(PyObject *inDataRef)
{
	if( inDataRef != Py_None ) {
		XPLMUnregisterDataAccessor(PyCapsule_GetPointer(inDataRef, "XPLMDataRef"));
	}
}

/***************************************************************************************
 * 						Data sharing
 ***************************************************************************************/

static std::map<void*, boost::python::object> sharedDataCallbacks;
static std::map<void*, boost::python::object> sharedDataRefCons;

void XPLMDataChanged_callback(void *inRefcon)
{
	boost::python::object &callback = sharedDataCallbacks.at(inRefcon);
	boost::python::object &refCon = sharedDataRefCons.at(inRefcon);
	callback(refCon);
}

int __XPLMShareData(	const char *inDataName,
						const XPLMDataTypeID &inDataType,
						const boost::python::object &inNotificationFunc,
						const boost::python::object &inNotificationRefcon)
{
	void *index = (void*)inDataName;
	sharedDataCallbacks[index] = inNotificationFunc;
	sharedDataRefCons[index] = inNotificationRefcon;

	const int ret =XPLMShareData(	inDataName,
									inDataType,
									inNotificationFunc.ptr() == Py_None ? NULL : XPLMDataChanged_callback,
									inNotificationRefcon.ptr() == Py_None ? NULL : PyCapsule_GetPointer(inNotificationRefcon.ptr(), "XPLMDataRef"));

	return ret;
}

int __XPLMUnshareData(	const char *inDataName,
        				const XPLMDataTypeID &inDataType,
						const boost::python::object &inNotificationFunc,
        				const boost::python::object &inNotificationRefcon)
{
	const int ret = XPLMUnshareData(inDataName,
									inDataType,
									inNotificationFunc.ptr() == Py_None ? NULL : XPLMDataChanged_callback,
									inNotificationRefcon.ptr() == Py_None ? NULL : PyCapsule_GetPointer(inNotificationRefcon.ptr(), "XPLMDataRef")
									);
	return ret;
}

