#include <iostream>

#define xstr(s) str(s)
#define str(s) #s

#define DEF_FUNCTION(NAME) def(xstr(NAME), NAME, NAME ## _doc)
