add_library( 
    ${PROJECT_NAME} 
    SHARED
    ${SHAKE_ALL_SOURCE_FILES}
)

set_target_properties(
    ${PROJECT_NAME}  
    PROPERTIES VERSION 
    ${PROJECT_VERSION})