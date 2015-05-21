#include <iostream>

#define xstr(s) _str(s)
#define _str(s) #s

#define DEF_FUNCTION(NAME) def(xstr(NAME), NAME, NAME ## _doc)

#define SCOPE_ATTR(NAME) scope().attr( #NAME ) = NAME
