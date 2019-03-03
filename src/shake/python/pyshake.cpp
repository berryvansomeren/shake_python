#include <pybind11/pybind11.h>

#include "main/application.hpp"

#include "submodules/submodules.hpp"

int add(int i, int j) {
    return i + j;
}


// This call must be in the global namespace
// However, we want to put all code that registers code,
// to be nicely put into our own namespaces.
// So this macro just delegates to our own functions.
PYBIND11_MODULE( SHAKE_PYTHON_LIBRARY_NAME, shake_module ) 
{
	shake_module.def("add", &add );

    shake::python::register_submodules( shake_module );
}


