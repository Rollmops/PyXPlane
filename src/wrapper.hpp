#ifndef _XPLANE_WRAPPER_HPP
#define _XPLANE_WRAPPER_HPP

#include <XPLMDataAccess.h>

#include <boost/python.hpp>

using namespace boost::python;

object __XPLMFindDataRef( const char *inDataRefName );



#endif // _XPLANE_WRAPPER_HPP
