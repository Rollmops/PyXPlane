#ifndef _PYXPLANE_DATAACCESS_WRAPPER_HPP
#define _PYXPLANE_DATAACCESS_WRAPPER_HPP

#include <XPLMDataAccess.h>
#include <boost/python.hpp>

PyObject *__XPLMFindDataRef(const char *inDataRefName);

int __XPLMCanWriteDataRef(PyObject *inDataRef);

XPLMDataTypeID __XPLMGetDataRefTypes(PyObject *inDataRef);

#endif // _PYXPLANE_DATAACCESS_WRAPPER_HPP
