#ifndef _PYXPLANE_DATAACCESS_WRAPPER_HPP
#define _PYXPLANE_DATAACCESS_WRAPPER_HPP

#include <XPLMDataAccess.h>
#include <boost/python.hpp>

#define GET_DATA(TYPE, SUFFIX) TYPE __XPLMGetData ## SUFFIX (PyObject *inDataRef) \
{\
	return XPLMGetData ##  SUFFIX (PyCapsule_GetPointer(inDataRef, "XPLMDataRef")); \
}

#define SET_DATA(TYPE, SUFFIX) void __XPLMSetData ## SUFFIX (PyObject *inDataRef, TYPE inValue) \
{ \
	XPLMSetData ## SUFFIX (PyCapsule_GetPointer(inDataRef, "XPLMDataRef"), inValue); \
}

#define GET_DATA_VECTOR(TYPE, SUFFIX) boost::python::list __XPLMGetDatav ## SUFFIX (PyObject *inDataRef, int inOffset, int inMax) \
{ \
	TYPE *outValues; \
	boost::python::list retList; \
	XPLMDataRef _inDataRef = PyCapsule_GetPointer(inDataRef, "XPLMDataRef"); \
	\
	if( inMax == -1 ) { \
		inMax = XPLMGetDatav ## SUFFIX (_inDataRef, NULL, 0, 0); \
	} \
	XPLMGetDatav ## SUFFIX (_inDataRef, outValues, inOffset, inMax); \
	\
	for(unsigned int i = 0; i < inMax; ++i) { \
		retList.append(outValues[i]); \
	} \
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


PyObject *__XPLMFindDataRef(const char *inDataRefName);

int __XPLMCanWriteDataRef(PyObject *inDataRef);

XPLMDataTypeID __XPLMGetDataRefTypes(PyObject *inDataRef);

int __XPLMGetDatai(PyObject *inDataRef);
float __XPLMGetDataf(PyObject *inDataRef);
double __XPLMGetDatad(PyObject *inDataRef);

void __XPLMSetDatai(PyObject *inDataRef, int inValue);
void __XPLMSetDataf(PyObject *inDataRef, float inValue);
void __XPLMSetDatad(PyObject *inDataRef, double inValue);

boost::python::list __XPLMGetDatavi (PyObject *inDataRef, int inOffset = 0, int inMax = -1);
boost::python::list __XPLMGetDatavf (PyObject *inDataRef, int inOffset = 0, int inMax = -1);
// TODO we assume that byte type returns always strings
std::string __XPLMGetDatab(PyObject *inDataRef, int inOffset = 0, int inMax = -1 );

void __XPLMSetDatavi(PyObject *inDataRef, const boost::python::list &inValues, int inOffset = 0, int inCount = -1);
void __XPLMSetDatavf(PyObject *inDataRef, const boost::python::list &inValues, int inOffset = 0, int inCount = -1);
// TODO we assume that byte type returns always strings
void __XPLMSetDatab(PyObject *inDataRef, const char *inValues, int inOffset = 0, int inCount = -1);

#endif // _PYXPLANE_DATAACCESS_WRAPPER_HPP
