#ifndef _PYXPLANE_DATAACCESS_WRAPPER_HPP
#define _PYXPLANE_DATAACCESS_WRAPPER_HPP

#include <XPLMDataAccess.h>

#include <boost/python.hpp>
#include <utility>
#include <iostream>
#include <algorithm>

#define NONE_TO_NULL(NAME) NAME == boost::python::object() ? NULL : NAME ## _callback

#define GET_DATA(TYPE, SUFFIX) TYPE __XPLMGetData ## SUFFIX (PyObject *inDataRef) \
{\
	if( inDataRef != Py_None ) { \
		return XPLMGetData ##  SUFFIX (PyCapsule_GetPointer(inDataRef, "XPLMDataRef")); \
	} \
	return 0; \
}

#define SET_DATA(TYPE, SUFFIX) void __XPLMSetData ## SUFFIX (PyObject *inDataRef, TYPE inValue) \
{ \
	if( inDataRef != Py_None ) { \
		XPLMSetData ## SUFFIX (PyCapsule_GetPointer(inDataRef, "XPLMDataRef"), inValue); \
	} \
}

#define GET_DATA_VECTOR(TYPE, SUFFIX) boost::python::list __XPLMGetDatav ## SUFFIX (PyObject *inDataRef, int inOffset, int inMax) \
{ \
	TYPE *outValues; \
	boost::python::list retList; \
	XPLMDataRef _inDataRef = NULL; \
	if (inDataRef != Py_None ) { \
		_inDataRef = PyCapsule_GetPointer(inDataRef, "XPLMDataRef"); \
	} else { \
		return retList; \
	}\
	if( inMax == -1 ) { \
		inMax = XPLMGetDatav ## SUFFIX (_inDataRef, NULL, 0, 0); \
	} \
	outValues = new TYPE[inMax - inOffset]; \
	const int n = XPLMGetDatav ## SUFFIX (_inDataRef, outValues, inOffset, inMax); \
	\
	for(unsigned int i = inOffset; i < n; ++i) { \
		retList.append(outValues[i]); \
	} \
	delete[] outValues; \
	return retList; \
}

#define SET_DATA_VECTOR(TYPE, SUFFIX) void __XPLMSetDatav ## SUFFIX (PyObject *inDataRef, const boost::python::list &inValues, int inOffset, int inCount) \
{ \
	const unsigned int listLength = boost::python::len(inValues); \
	if( inCount == -1 || inCount > listLength) { \
		inCount = listLength; \
	} \
	TYPE _inValues[inCount]; \
	for( unsigned int i=0; i < inCount; ++i ) \
	{ \
		_inValues[i] = boost::python::extract<TYPE>(inValues[i]); \
	} \
	XPLMSetDatav ## SUFFIX (PyCapsule_GetPointer(inDataRef, "XPLMDataRef"), _inValues, inOffset, inCount); \
}


#define READ_CALLBACK(NAME, TYPE) TYPE NAME ## _callback(void *index) \
{ \
	const DataAccessorCallbacksStruct &callback = callbackMap.at(index); \
	const boost::python::object &refCon = refConReadMap.at(index); \
	return boost::python::extract<TYPE>(callback.NAME(refCon)); \
}

#define WRITE_CALLBACK(NAME, TYPE) void NAME ## _callback(void *index, TYPE value) \
{ \
	const DataAccessorCallbacksStruct &callback = callbackMap.at(index); \
	const boost::python::object &refCon = refConWriteMap.at(index); \
	callback.NAME(refCon, value); \
}

#define READ_ARRAY_CALLBACK(NAME, TYPE) int NAME ## _callback(void *indexPtr, TYPE *outValues, int inOffset, int inMax) \
{ \
	const boost::python::object &refCon = refConReadMap.at(indexPtr); \
	const boost::python::object &callback = callbackMap.at(indexPtr).NAME; \
	boost::python::list retList = boost::python::extract<boost::python::list>(callback(refCon)); \
	const boost::python::ssize_t n = boost::python::len(retList); \
	if( outValues == NULL ) { \
		return n; \
	} \
	const int minLength = std::min(inMax, static_cast<int>(n)); \
	for(boost::python::ssize_t i=inOffset;i < minLength;++i) { \
		boost::python::object elem = retList[i]; \
		outValues[i] = boost::python::extract<TYPE>(elem); \
	} \
	return n; \
}

#define WRITE_ARRAY_CALLBACK(NAME, TYPE) void NAME ## _callback(void *index, TYPE *inValues, int inOffset, int inMax) \
{ \
	const DataAccessorCallbacksStruct &callback = callbackMap.at(index); \
	const boost::python::object &refCon = refConWriteMap.at(index); \
\
	boost::python::list writeList; \
	for(unsigned int i=0;i<inMax;++i) { \
		writeList.append(inValues[i]); \
	} \
\
	callback.inWriteIntArray(refCon, writeList, inOffset, inMax); \
}

PyObject *__XPLMFindDataRef(const char *inDataRefName);

int __XPLMCanWriteDataRef(PyObject *inDataRef);

XPLMDataTypeID __XPLMGetDataRefTypes(PyObject *inDataRef);

int __XPLMGetDatai(PyObject *inDataRef);
double __XPLMGetDataf(PyObject *inDataRef);
double __XPLMGetDatad(PyObject *inDataRef);

void __XPLMSetDatai(PyObject *inDataRef, int inValue);
void __XPLMSetDataf(PyObject *inDataRef, float inValue);
void __XPLMSetDatad(PyObject *inDataRef, double inValue);

boost::python::list __XPLMGetDatavi (PyObject *inDataRef, int inOffset = 0, int inMax = -1);
BOOST_PYTHON_FUNCTION_OVERLOADS(__XPLMGetDatavi_overloads, __XPLMGetDatavi, 1, 3);
boost::python::list __XPLMGetDatavf (PyObject *inDataRef, int inOffset = 0, int inMax = -1);
BOOST_PYTHON_FUNCTION_OVERLOADS(__XPLMGetDatavf_overloads, __XPLMGetDatavf, 1, 3);

// TODO we assume that byte type returns always strings
std::string __XPLMGetDatab(PyObject *inDataRef, int inOffset = 0, int inMax = -1 );

void __XPLMSetDatavi(PyObject *inDataRef, const boost::python::list &inValues, int inOffset = 0, int inCount = -1);
BOOST_PYTHON_FUNCTION_OVERLOADS(__XPLMSetDatavi_overloads, __XPLMSetDatavi, 2, 4);
void __XPLMSetDatavf(PyObject *inDataRef, const boost::python::list &inValues, int inOffset = 0, int inCount = -1);
BOOST_PYTHON_FUNCTION_OVERLOADS(__XPLMSetDatavf_overloads, __XPLMSetDatavf, 2, 4);

// TODO we assume that byte type returns always strings
void __XPLMSetDatab(PyObject *inDataRef, const char *inValues, int inOffset = 0, int inCount = -1);
BOOST_PYTHON_FUNCTION_OVERLOADS(__XPLMSetDatab_overloads, __XPLMSetDatab, 2, 4);

struct DataAccessorCallbacksStruct
{
	boost::python::object	inReadInt;
	boost::python::object	inWriteInt;
	boost::python::object	inReadFloat;
	boost::python::object	inWriteFloat;
	boost::python::object	inReadDouble;
	boost::python::object	inWriteDouble;
	boost::python::object	inReadIntArray;
	boost::python::object	inWriteIntArray;
	boost::python::object	inReadFloatArray;
	boost::python::object	inWriteFloatArray;
	boost::python::object	inReadData;
	boost::python::object	inWriteData;
};


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
								   );


void __XPLMUnregisterDataAccessor(PyObject *inDataRef);

int __XPLMShareData(	const char *inDataName,
						const XPLMDataTypeID &inDataTyp,
						const boost::python::object &inNotificationFunc,
						const boost::python::object &inNotificationRefcon);

int __XPLMUnshareData(	const char *inDataName,
        				const XPLMDataTypeID &inDataType,
						const boost::python::object &inNotificationFunc,
        				const boost::python::object &inNotificationRefcon);


#endif // _PYXPLANE_DATAACCESS_WRAPPER_HPP
