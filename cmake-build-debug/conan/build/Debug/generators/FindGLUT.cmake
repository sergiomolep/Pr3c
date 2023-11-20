########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(GLUT_FIND_QUIETLY)
    set(GLUT_MESSAGE_MODE VERBOSE)
else()
    set(GLUT_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/module-GLUTTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${freeglut_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(GLUT_VERSION_STRING "3.4.0")
set(GLUT_INCLUDE_DIRS ${freeglut_INCLUDE_DIRS_DEBUG} )
set(GLUT_INCLUDE_DIR ${freeglut_INCLUDE_DIRS_DEBUG} )
set(GLUT_LIBRARIES ${freeglut_LIBRARIES_DEBUG} )
set(GLUT_DEFINITIONS ${freeglut_DEFINITIONS_DEBUG} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${freeglut_BUILD_MODULES_PATHS_DEBUG} )
    message(${GLUT_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


include(FindPackageHandleStandardArgs)
set(GLUT_FOUND 1)
set(GLUT_VERSION "3.4.0")

find_package_handle_standard_args(GLUT
                                  REQUIRED_VARS GLUT_VERSION
                                  VERSION_VAR GLUT_VERSION)
mark_as_advanced(GLUT_FOUND GLUT_VERSION)
