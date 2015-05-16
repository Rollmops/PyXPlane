#include "wrapper.hpp"

object __XPLMFindDataRef( const char *inDataRefName )
{
	const void *ret = XPLMFindDataRef(inDataRefName);
	return object(1);
}
