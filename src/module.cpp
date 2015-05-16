#include <boost/python.hpp>
#include "common.hpp"

#include "wrapper.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(_binding)
{
	scope().attr("__version__") = std::string(xstr(__BINDING_VERSION__));

	def("XPLMFindDataRef", __XPLMFindDataRef);

}
