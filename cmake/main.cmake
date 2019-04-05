#----------------------------------------------------------------
# The libshake project contains the shake executable

# Create project
set( PROJECT_NAME shake_python )
set( SHAKE_PYTHON_LIBRARY_NAME pyshake )
project( ${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX )
include( cmake/config.cmake )

# Create external targets
include( cmake/create_external_targets.cmake )

# Glob files
include( cmake/glob_files.cmake )

# Create library
include( cmake/compiler.cmake )
include( cmake/create_library.cmake )

# Link dependencies
include( cmake/link_dependencies.cmake )