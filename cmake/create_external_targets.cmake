#----------------------------------------------------------------
# Create the external targets that our project relies on

# pybind11
set(PYBIND11_CPP_STANDARD -std=c++17)
add_subdirectory( external/pybind11-2.2.3 )
# also needs an installed Python version (We use Python3)


# a list of all include directories
set( SHAKE_INCLUDE_DIRECTORIES 
	src/
    external/
	${PYBIND11_INCLUDE_DIR} # defined by pybind11
	${PYTHON_INCLUDE_DIRS}	# defined by pybind11
	C:/Users/Berry/Documents/shake3/shake_content/src/
	C:/Users/Berry/Documents/shake3/shake_core/src/
	C:/Users/Berry/Documents/shake3/shake_ecs/src/
	C:/Users/Berry/Documents/shake3/shake_graphics/src/
	C:/Users/Berry/Documents/shake3/shake_hid/src/
	C:/Users/Berry/Documents/shake3/shake_io/src/
	C:/Users/Berry/Documents/shake3/shake_main/src/
)

# a list of all external libraries
set( SHAKE_EXTERNAL_LIBRARIES 
	${EXECUTABLE_NAME}
    pybind11
	${PYTHON_LIBRARIES}		# defined by pybind11
	shake_content
	shake_core
	shake_ecs
	shake_graphics
	shake_hid
	shake_io
	shake_main
)