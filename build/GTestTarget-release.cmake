########## MACROS ###########################################################################
#############################################################################################


macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS FRAMEWORKS_DIRS)
    if(APPLE)
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAMES ${_FRAMEWORK} PATHS ${FRAMEWORKS_DIRS} CMAKE_FIND_ROOT_PATH_BOTH)
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${FRAMEWORKS_DIRS}")
            endif()
        endforeach()
    endif()
endmacro()


function(conan_package_library_targets libraries package_libdir deps out_libraries out_libraries_target build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAMES ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            list(APPEND _out_libraries ${CONAN_FOUND_LIBRARY})
            if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
                # Create a micro-target for each lib/a found
                string(REGEX REPLACE "[^A-Za-z0-9.+_-]" "_" _LIBRARY_NAME ${_LIBRARY_NAME})
                set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
                if(NOT TARGET ${_LIB_NAME})
                    # Create a micro-target for each lib/a found
                    add_library(${_LIB_NAME} UNKNOWN IMPORTED)
                    set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
                    set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
                else()
                    conan_message(STATUS "Skipping already existing target: ${_LIB_NAME}")
                endif()
                list(APPEND _out_libraries_target ${_LIB_NAME})
            endif()
            conan_message(STATUS "Found: ${CONAN_FOUND_LIBRARY}")
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            list(APPEND _out_libraries_target ${_LIBRARY_NAME})
            list(APPEND _out_libraries ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
        # Add all dependencies to all targets
        string(REPLACE " " ";" deps_list "${deps}")
        foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
            set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
        endforeach()
    endif()

    set(${out_libraries} ${_out_libraries} PARENT_SCOPE)
    set(${out_libraries_target} ${_out_libraries_target} PARENT_SCOPE)
endfunction()


########### VARIABLES #######################################################################
#############################################################################################


set(GTest_INCLUDE_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_INCLUDE_DIR_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_INCLUDES_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_RES_DIRS_RELEASE )
set(GTest_DEFINITIONS_RELEASE )
set(GTest_LINKER_FLAGS_RELEASE_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)
set(GTest_COMPILE_DEFINITIONS_RELEASE )
set(GTest_COMPILE_OPTIONS_RELEASE_LIST "" "")
set(GTest_COMPILE_OPTIONS_C_RELEASE "")
set(GTest_COMPILE_OPTIONS_CXX_RELEASE "")
set(GTest_LIBRARIES_TARGETS_RELEASE "") # Will be filled later, if CMake 3
set(GTest_LIBRARIES_RELEASE "") # Will be filled later
set(GTest_LIBS_RELEASE "") # Same as GTest_LIBRARIES
set(GTest_SYSTEM_LIBS_RELEASE )
set(GTest_FRAMEWORK_DIRS_RELEASE )
set(GTest_FRAMEWORKS_RELEASE )
set(GTest_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
set(GTest_BUILD_MODULES_PATHS_RELEASE )

conan_find_apple_frameworks(GTest_FRAMEWORKS_FOUND_RELEASE "${GTest_FRAMEWORKS_RELEASE}" "${GTest_FRAMEWORK_DIRS_RELEASE}")

mark_as_advanced(GTest_INCLUDE_DIRS_RELEASE
                 GTest_INCLUDE_DIR_RELEASE
                 GTest_INCLUDES_RELEASE
                 GTest_DEFINITIONS_RELEASE
                 GTest_LINKER_FLAGS_RELEASE_LIST
                 GTest_COMPILE_DEFINITIONS_RELEASE
                 GTest_COMPILE_OPTIONS_RELEASE_LIST
                 GTest_LIBRARIES_RELEASE
                 GTest_LIBS_RELEASE
                 GTest_LIBRARIES_TARGETS_RELEASE)

# Find the real .lib/.a and add them to GTest_LIBS and GTest_LIBRARY_LIST
set(GTest_LIBRARY_LIST_RELEASE gtest_main gmock_main gmock gtest)
set(GTest_LIB_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/lib")

# Gather all the libraries that should be linked to the targets (do not touch existing variables):
set(_GTest_DEPENDENCIES_RELEASE "${GTest_FRAMEWORKS_FOUND_RELEASE} ${GTest_SYSTEM_LIBS_RELEASE} ")

conan_package_library_targets("${GTest_LIBRARY_LIST_RELEASE}"  # libraries
                              "${GTest_LIB_DIRS_RELEASE}"      # package_libdir
                              "${_GTest_DEPENDENCIES_RELEASE}"  # deps
                              GTest_LIBRARIES_RELEASE            # out_libraries
                              GTest_LIBRARIES_TARGETS_RELEASE    # out_libraries_targets
                              "_RELEASE"                          # build_type
                              "GTest")                                      # package_name

set(GTest_LIBS_RELEASE ${GTest_LIBRARIES_RELEASE})

foreach(_FRAMEWORK ${GTest_FRAMEWORKS_FOUND_RELEASE})
    list(APPEND GTest_LIBRARIES_TARGETS_RELEASE ${_FRAMEWORK})
    list(APPEND GTest_LIBRARIES_RELEASE ${_FRAMEWORK})
endforeach()

foreach(_SYSTEM_LIB ${GTest_SYSTEM_LIBS_RELEASE})
    list(APPEND GTest_LIBRARIES_TARGETS_RELEASE ${_SYSTEM_LIB})
    list(APPEND GTest_LIBRARIES_RELEASE ${_SYSTEM_LIB})
endforeach()

# We need to add our requirements too
set(GTest_LIBRARIES_TARGETS_RELEASE "${GTest_LIBRARIES_TARGETS_RELEASE};")
set(GTest_LIBRARIES_RELEASE "${GTest_LIBRARIES_RELEASE};")

set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH  ${CMAKE_PREFIX_PATH})

set(GTest_COMPONENTS_RELEASE GTest::gtest_main GTest::gmock_main GTest::gmock GTest::gtest)

########### COMPONENT gtest VARIABLES #############################################

set(GTest_gtest_INCLUDE_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gtest_INCLUDE_DIR_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gtest_INCLUDES_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gtest_LIB_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/lib")
set(GTest_gtest_RES_DIRS_RELEASE )
set(GTest_gtest_DEFINITIONS_RELEASE )
set(GTest_gtest_COMPILE_DEFINITIONS_RELEASE )
set(GTest_gtest_COMPILE_OPTIONS_C_RELEASE "")
set(GTest_gtest_COMPILE_OPTIONS_CXX_RELEASE "")
set(GTest_gtest_LIBS_RELEASE gtest)
set(GTest_gtest_SYSTEM_LIBS_RELEASE )
set(GTest_gtest_FRAMEWORK_DIRS_RELEASE )
set(GTest_gtest_FRAMEWORKS_RELEASE )
set(GTest_gtest_BUILD_MODULES_PATHS_RELEASE )
set(GTest_gtest_DEPENDENCIES_RELEASE )
set(GTest_gtest_LINKER_FLAGS_LIST_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>
)

########## COMPONENT gtest FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #############

set(GTest_gtest_FRAMEWORKS_FOUND_RELEASE "")
conan_find_apple_frameworks(GTest_gtest_FRAMEWORKS_FOUND_RELEASE "${GTest_gtest_FRAMEWORKS_RELEASE}" "${GTest_gtest_FRAMEWORK_DIRS_RELEASE}")

set(GTest_gtest_LIB_TARGETS_RELEASE "")
set(GTest_gtest_NOT_USED_RELEASE "")
set(GTest_gtest_LIBS_FRAMEWORKS_DEPS_RELEASE ${GTest_gtest_FRAMEWORKS_FOUND_RELEASE} ${GTest_gtest_SYSTEM_LIBS_RELEASE} ${GTest_gtest_DEPENDENCIES_RELEASE})
conan_package_library_targets("${GTest_gtest_LIBS_RELEASE}"
                              "${GTest_gtest_LIB_DIRS_RELEASE}"
                              "${GTest_gtest_LIBS_FRAMEWORKS_DEPS_RELEASE}"
                              GTest_gtest_NOT_USED_RELEASE
                              GTest_gtest_LIB_TARGETS_RELEASE
                              "RELEASE"
                              "GTest_gtest")

set(GTest_gtest_LINK_LIBS_RELEASE ${GTest_gtest_LIB_TARGETS_RELEASE} ${GTest_gtest_LIBS_FRAMEWORKS_DEPS_RELEASE})

########### COMPONENT gmock VARIABLES #############################################

set(GTest_gmock_INCLUDE_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gmock_INCLUDE_DIR_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gmock_INCLUDES_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gmock_LIB_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/lib")
set(GTest_gmock_RES_DIRS_RELEASE )
set(GTest_gmock_DEFINITIONS_RELEASE )
set(GTest_gmock_COMPILE_DEFINITIONS_RELEASE )
set(GTest_gmock_COMPILE_OPTIONS_C_RELEASE "")
set(GTest_gmock_COMPILE_OPTIONS_CXX_RELEASE "")
set(GTest_gmock_LIBS_RELEASE gmock)
set(GTest_gmock_SYSTEM_LIBS_RELEASE )
set(GTest_gmock_FRAMEWORK_DIRS_RELEASE )
set(GTest_gmock_FRAMEWORKS_RELEASE )
set(GTest_gmock_BUILD_MODULES_PATHS_RELEASE )
set(GTest_gmock_DEPENDENCIES_RELEASE GTest::gtest)
set(GTest_gmock_LINKER_FLAGS_LIST_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>
)

########## COMPONENT gmock FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #############

set(GTest_gmock_FRAMEWORKS_FOUND_RELEASE "")
conan_find_apple_frameworks(GTest_gmock_FRAMEWORKS_FOUND_RELEASE "${GTest_gmock_FRAMEWORKS_RELEASE}" "${GTest_gmock_FRAMEWORK_DIRS_RELEASE}")

set(GTest_gmock_LIB_TARGETS_RELEASE "")
set(GTest_gmock_NOT_USED_RELEASE "")
set(GTest_gmock_LIBS_FRAMEWORKS_DEPS_RELEASE ${GTest_gmock_FRAMEWORKS_FOUND_RELEASE} ${GTest_gmock_SYSTEM_LIBS_RELEASE} ${GTest_gmock_DEPENDENCIES_RELEASE})
conan_package_library_targets("${GTest_gmock_LIBS_RELEASE}"
                              "${GTest_gmock_LIB_DIRS_RELEASE}"
                              "${GTest_gmock_LIBS_FRAMEWORKS_DEPS_RELEASE}"
                              GTest_gmock_NOT_USED_RELEASE
                              GTest_gmock_LIB_TARGETS_RELEASE
                              "RELEASE"
                              "GTest_gmock")

set(GTest_gmock_LINK_LIBS_RELEASE ${GTest_gmock_LIB_TARGETS_RELEASE} ${GTest_gmock_LIBS_FRAMEWORKS_DEPS_RELEASE})

########### COMPONENT gmock_main VARIABLES #############################################

set(GTest_gmock_main_INCLUDE_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gmock_main_INCLUDE_DIR_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gmock_main_INCLUDES_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gmock_main_LIB_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/lib")
set(GTest_gmock_main_RES_DIRS_RELEASE )
set(GTest_gmock_main_DEFINITIONS_RELEASE )
set(GTest_gmock_main_COMPILE_DEFINITIONS_RELEASE )
set(GTest_gmock_main_COMPILE_OPTIONS_C_RELEASE "")
set(GTest_gmock_main_COMPILE_OPTIONS_CXX_RELEASE "")
set(GTest_gmock_main_LIBS_RELEASE gmock_main)
set(GTest_gmock_main_SYSTEM_LIBS_RELEASE )
set(GTest_gmock_main_FRAMEWORK_DIRS_RELEASE )
set(GTest_gmock_main_FRAMEWORKS_RELEASE )
set(GTest_gmock_main_BUILD_MODULES_PATHS_RELEASE )
set(GTest_gmock_main_DEPENDENCIES_RELEASE GTest::gmock)
set(GTest_gmock_main_LINKER_FLAGS_LIST_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>
)

########## COMPONENT gmock_main FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #############

set(GTest_gmock_main_FRAMEWORKS_FOUND_RELEASE "")
conan_find_apple_frameworks(GTest_gmock_main_FRAMEWORKS_FOUND_RELEASE "${GTest_gmock_main_FRAMEWORKS_RELEASE}" "${GTest_gmock_main_FRAMEWORK_DIRS_RELEASE}")

set(GTest_gmock_main_LIB_TARGETS_RELEASE "")
set(GTest_gmock_main_NOT_USED_RELEASE "")
set(GTest_gmock_main_LIBS_FRAMEWORKS_DEPS_RELEASE ${GTest_gmock_main_FRAMEWORKS_FOUND_RELEASE} ${GTest_gmock_main_SYSTEM_LIBS_RELEASE} ${GTest_gmock_main_DEPENDENCIES_RELEASE})
conan_package_library_targets("${GTest_gmock_main_LIBS_RELEASE}"
                              "${GTest_gmock_main_LIB_DIRS_RELEASE}"
                              "${GTest_gmock_main_LIBS_FRAMEWORKS_DEPS_RELEASE}"
                              GTest_gmock_main_NOT_USED_RELEASE
                              GTest_gmock_main_LIB_TARGETS_RELEASE
                              "RELEASE"
                              "GTest_gmock_main")

set(GTest_gmock_main_LINK_LIBS_RELEASE ${GTest_gmock_main_LIB_TARGETS_RELEASE} ${GTest_gmock_main_LIBS_FRAMEWORKS_DEPS_RELEASE})

########### COMPONENT gtest_main VARIABLES #############################################

set(GTest_gtest_main_INCLUDE_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gtest_main_INCLUDE_DIR_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gtest_main_INCLUDES_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/include")
set(GTest_gtest_main_LIB_DIRS_RELEASE "C:/Users/WB274724/.conan/data/gtest/1.13.0/_/_/package/10f3c0a3a24a1055f3670e6694da4a93d078e663/lib")
set(GTest_gtest_main_RES_DIRS_RELEASE )
set(GTest_gtest_main_DEFINITIONS_RELEASE )
set(GTest_gtest_main_COMPILE_DEFINITIONS_RELEASE )
set(GTest_gtest_main_COMPILE_OPTIONS_C_RELEASE "")
set(GTest_gtest_main_COMPILE_OPTIONS_CXX_RELEASE "")
set(GTest_gtest_main_LIBS_RELEASE gtest_main)
set(GTest_gtest_main_SYSTEM_LIBS_RELEASE )
set(GTest_gtest_main_FRAMEWORK_DIRS_RELEASE )
set(GTest_gtest_main_FRAMEWORKS_RELEASE )
set(GTest_gtest_main_BUILD_MODULES_PATHS_RELEASE )
set(GTest_gtest_main_DEPENDENCIES_RELEASE GTest::gtest)
set(GTest_gtest_main_LINKER_FLAGS_LIST_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>
)

########## COMPONENT gtest_main FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #############

set(GTest_gtest_main_FRAMEWORKS_FOUND_RELEASE "")
conan_find_apple_frameworks(GTest_gtest_main_FRAMEWORKS_FOUND_RELEASE "${GTest_gtest_main_FRAMEWORKS_RELEASE}" "${GTest_gtest_main_FRAMEWORK_DIRS_RELEASE}")

set(GTest_gtest_main_LIB_TARGETS_RELEASE "")
set(GTest_gtest_main_NOT_USED_RELEASE "")
set(GTest_gtest_main_LIBS_FRAMEWORKS_DEPS_RELEASE ${GTest_gtest_main_FRAMEWORKS_FOUND_RELEASE} ${GTest_gtest_main_SYSTEM_LIBS_RELEASE} ${GTest_gtest_main_DEPENDENCIES_RELEASE})
conan_package_library_targets("${GTest_gtest_main_LIBS_RELEASE}"
                              "${GTest_gtest_main_LIB_DIRS_RELEASE}"
                              "${GTest_gtest_main_LIBS_FRAMEWORKS_DEPS_RELEASE}"
                              GTest_gtest_main_NOT_USED_RELEASE
                              GTest_gtest_main_LIB_TARGETS_RELEASE
                              "RELEASE"
                              "GTest_gtest_main")

set(GTest_gtest_main_LINK_LIBS_RELEASE ${GTest_gtest_main_LIB_TARGETS_RELEASE} ${GTest_gtest_main_LIBS_FRAMEWORKS_DEPS_RELEASE})