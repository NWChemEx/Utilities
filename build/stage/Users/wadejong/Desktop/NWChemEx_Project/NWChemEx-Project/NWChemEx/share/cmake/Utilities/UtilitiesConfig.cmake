################################################################################
#                                                                              #
# This file generated from NWChemExTargetConfig.cmake.in. Do not edit.         #
#                                                                              #
################################################################################

include(FindPackageHandleStandardArgs)
find_package(CMakeBuild REQUIRED)
include(AssertMacros)
#Get the install root by assuming we are in root/share/cmake/ProjectName
set(INSTALL_ROOT      "${CMAKE_CURRENT_LIST_DIR}") #ProjectName/

foreach(__iter RANGE 2)
    get_filename_component(INSTALL_ROOT "${INSTALL_ROOT}" DIRECTORY)
endforeach()

#Name of the library
set(__name Utilities)
string(TOUPPER ${__name} __NAME)

#Find the actual library (if there is one)
if(TRUE)
    find_library(${__NAME}_LIBRARY ${__name}
                 PATHS ${INSTALL_ROOT}/lib/${__name})
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(${__NAME} DEFAULT_MSG ${__NAME}_LIBRARY)
endif()

#Find paths to all header files part of the public API
set(__headers Any.hpp;Containers/CaseInsensitiveMap.hpp;Containers/MathSet.hpp;Mathematician/Combinatorics.hpp;Mathematician/IntegerUtils.hpp;IterTools/CartesianProduct.hpp;IterTools/Combinations.hpp;IterTools/Enumerate.hpp;IterTools/Permutations.hpp;IterTools/Range.hpp;IterTools/RangeContainer.hpp;IterTools/TupleContainer.hpp;IterTools/Zip.hpp;TypeTraits/IteratorTypes.hpp;TypeTraits/TupleUtilities.hpp;TypeTraits/type_traitsExtensions.hpp)
foreach(__header_i ${__headers})
   get_filename_component(__file_name ${__header_i} NAME_WE)

   #Make a list of where we found each header file and ensure they all have
   #the same include path
   list(APPEND ${__name}_HEADERS ${__file_name}_INCLUDE_DIR)

   #If another dependency has the same include this value is still set..
   unset(${__file_name}_INCLUDE_DIR CACHE)
   find_path(${__file_name}_INCLUDE_DIR ${__name}/${__header_i}
             PATHS ${INSTALL_ROOT}/include)
   #All header files better result in same include path...
   if(${__NAME}_INCLUDE_DIR)
       assert_strings_are_equal(${__NAME}_INCLUDE_DIR
                                ${__file_name}_INCLUDE_DIR)
   else()
       set(${__NAME}_INCLUDE_DIR ${${__file_name}_INCLUDE_DIR})
   endif()
endforeach()
FIND_PACKAGE_HANDLE_STANDARD_ARGS(${__NAME} DEFAULT_MSG  "${${__name}_HEADERS}")

#find_package will only crash for a variable of the same case
set(${__name}_FOUND ${${__NAME}_FOUND})


set(${__NAME}_LIBRARIES ${${__NAME}_LIBRARY})
set(${__NAME}_INCLUDE_DIRS ${${__NAME}_INCLUDE_DIR})

#Find the dependencies
include(DependencyMacros)
set(__depends )
foreach(__depend_i ${__depends})
    find_dependency(${__depend_i} ${__NAME}_INCLUDE_DIRS
                                  ${__NAME}_LIBRARIES
                                  ${__NAME}_DEFINITIONS
                                  ${__NAME}_LINK_FLAGS
                                  ${__NAME}_FOUND)
endforeach()

#Print our hardwork out
message(STATUS "Found ${__name} include paths: ${${__NAME}_INCLUDE_DIRS}")
message(STATUS "Found ${__name} libraries: ${${__NAME}_LIBRARIES}")
message(STATUS "Found ${__name} definitions: ${${__NAME}_DEFINITIONS}")
