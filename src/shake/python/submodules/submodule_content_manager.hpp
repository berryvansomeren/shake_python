#ifndef MODULE_CONTENT_MANAGER_HPP
#define MODULE_CONTENT_MANAGER_HPP


#include <pybind11/pybind11.h>


namespace shake {
namespace python {


//----------------------------------------------------------------
void register_content_manager
(
	pybind11::module& shake_module
);


} // namespace python
} // namespace shake

#endif // MODULE_CONTENT_MANAGER_HPP
