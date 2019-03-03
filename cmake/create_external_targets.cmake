#----------------------------------------------------------------
# Create the external targets that our project relies on

# pybind11
add_subdirectory( external/pybind11-2.2.3 )
# also needs an installed Python version (We use Python3)
 
# GLFW options
option( GLFW_INSTALL			OFF )
option( GLFW_BUILD_DOCS			OFF )
option( GLFW_BUILD_EXAMPLES		OFF )
option( GLFW_BUILD_TESTS		OFF )
add_subdirectory( external/glfw ) 

# Freetype 
add_subdirectory( external/freetype-2.9/ )


# a list of all include directories
set( SHAKE_INCLUDE_DIRECTORIES 
	src/
    external/
    external/freetype-2.9/include/
    external/glad/include/
    external/glfw/include/
    external/glm/
    external/json11/
    external/lua-5.3.4/src/
    external/stb/
	${PYBIND11_INCLUDE_DIR} # defined by pybind11
	${PYTHON_INCLUDE_DIRS}	# defined by pybind11
	C:/Users/Berry/Documents/shake3/shake_content/src/
	C:/Users/Berry/Documents/shake3/shake_core/src/
	C:/Users/Berry/Documents/shake3/shake_ecs/src/
	C:/Users/Berry/Documents/shake3/shake_graphics/src/
	C:/Users/Berry/Documents/shake3/shake_hid/src/
	C:/Users/Berry/Documents/shake3/shake_io/src/
	C:/Users/Berry/Documents/shake3/shake_scene/src/
)

# a list of all external libraries
set( SHAKE_EXTERNAL_LIBRARIES 
	${EXECUTABLE_NAME}
    glfw
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
    freetype
    pybind11
	${PYTHON_LIBRARIES}		# defined by pybind11
	shake_core
	shake_ecs
	shake_graphics
	shake_hid
	shake_io
	shake_scene
)