# pybind creates the library of Python bindings for us
pybind11_add_module( ${SHAKE_PYTHON_LIBRARY_NAME} SHARED ${SHAKE_ALL_SOURCE_FILES} ) 