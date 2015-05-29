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

static std::map<void *, DataAccessorCallbacks> callbackMap;
static std::map<void *, boost::python::object> refConReadMap;
static std::map<void *, boost::python::object> refConWriteMap;

int inReadInt_callback(void *index)
{
	DataAccessorCallbacks &callback = callbackMap.at(index);
	boost::python::object &refCon = refConReadMap.at(index);
	return boost::python::extract<int>(callback.inReadInt(refCon));
}


float inReadFloat_callback(void *index)
{
	DataAccessorCallbacks &callback = callbackMap.at(index);
	boost::python::object &refCon = refConReadMap.at(index);
	return boost::python::extract<float>(callback.inReadFloat(refCon));
}

double inReadDouble_callback(void *index)
{
	DataAccessorCallbacks &callback = callbackMap.at(index);
	boost::python::object &refCon = refConReadMap.at(index);
	return boost::python::extract<double>(callback.inReadDouble(refCon));
}

#define NONE_TO_NULL(NAME) NAME == boost::python::object() ? NULL : NAME ## _callback

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
// TODO use shared_ptr
	static unsigned int index = 0;
	void* indexPtr = (void*)(new unsigned int(index++));

	refConReadMap[indexPtr] = inReadRefCon;
	refConWriteMap[indexPtr] = inWriteRefCon;
	DataAccessorCallbacks &callbacks = callbackMap[indexPtr];

	XPLMDataRef ref = XPLMRegisterDataAccessor(inDataName, inDataType, inIsWritable,
			NONE_TO_NULL(inReadInt), NULL,
			NONE_TO_NULL(inReadFloat), NULL,
			NONE_TO_NULL(inReadDouble), NULL,
			NULL, NULL,
			NULL, NULL,
			NULL, NULL,
			indexPtr,
			indexPtr);

	callbacks.inReadInt = inReadInt;
	callbacks.inReadFloat = inReadFloat;
	callbacks.inReadDouble = inReadDouble;

	PyObject *ret = PyCapsule_New(ref, "XPLMDataRef", NULL);
	return ret;
}
