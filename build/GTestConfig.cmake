########## MACROS ###########################################################################
#############################################################################################

function(conan_message MESSAGE_OUTPUT)
    if(NOT CONAN_CMAKE_SILENT_OUTPUT)
        message(${ARGV${0}})
    endif()
endfunction()


# Requires CMake > 3.0
if(${CMAKE_VERSION} VERSION_LESS "3.0")
    message(FATAL_ERROR "The 'cmake_find_package_multi' generator only works with CMake > 3.0")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/GTestTargets.cmake)

########## FIND PACKAGE DEPENDENCY ##########################################################
#############################################################################################

include(CMakeFindDependencyMacro)

########## TARGETS PROPERTIES ###############################################################
#############################################################################################

########## COMPONENT gtest TARGET PROPERTIES ######################################

set_property(TARGET GTest::gtest PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${GTest_gtest_LINK_LIBS_DEBUG}
                ${GTest_gtest_LINKER_FLAGS_LIST_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gtest_LINK_LIBS_RELEASE}
                ${GTest_gtest_LINKER_FLAGS_LIST_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gtest_LINK_LIBS_RELWITHDEBINFO}
                ${GTest_gtest_LINKER_FLAGS_LIST_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gtest_LINK_LIBS_MINSIZEREL}
                ${GTest_gtest_LINKER_FLAGS_LIST_MINSIZEREL}>)
set_property(TARGET GTest::gtest PROPERTY INTERFACE_INCLUDE_DIRECTORIES
             $<$<CONFIG:Debug>:${GTest_gtest_INCLUDE_DIRS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gtest_INCLUDE_DIRS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gtest_INCLUDE_DIRS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gtest_INCLUDE_DIRS_MINSIZEREL}>)
set_property(TARGET GTest::gtest PROPERTY INTERFACE_COMPILE_DEFINITIONS
             $<$<CONFIG:Debug>:${GTest_gtest_COMPILE_DEFINITIONS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gtest_COMPILE_DEFINITIONS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gtest_COMPILE_DEFINITIONS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gtest_COMPILE_DEFINITIONS_MINSIZEREL}>)
set_property(TARGET GTest::gtest PROPERTY INTERFACE_COMPILE_OPTIONS
             $<$<CONFIG:Debug>:
                 ${GTest_gtest_COMPILE_OPTIONS_C_DEBUG}
                 ${GTest_gtest_COMPILE_OPTIONS_CXX_DEBUG}>
             $<$<CONFIG:Release>:
                 ${GTest_gtest_COMPILE_OPTIONS_C_RELEASE}
                 ${GTest_gtest_COMPILE_OPTIONS_CXX_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:
                 ${GTest_gtest_COMPILE_OPTIONS_C_RELWITHDEBINFO}
                 ${GTest_gtest_COMPILE_OPTIONS_CXX_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:
                 ${GTest_gtest_COMPILE_OPTIONS_C_MINSIZEREL}
                 ${GTest_gtest_COMPILE_OPTIONS_CXX_MINSIZEREL}>)
set(GTest_gtest_TARGET_PROPERTIES TRUE)

########## COMPONENT gmock TARGET PROPERTIES ######################################

set_property(TARGET GTest::gmock PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${GTest_gmock_LINK_LIBS_DEBUG}
                ${GTest_gmock_LINKER_FLAGS_LIST_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gmock_LINK_LIBS_RELEASE}
                ${GTest_gmock_LINKER_FLAGS_LIST_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gmock_LINK_LIBS_RELWITHDEBINFO}
                ${GTest_gmock_LINKER_FLAGS_LIST_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gmock_LINK_LIBS_MINSIZEREL}
                ${GTest_gmock_LINKER_FLAGS_LIST_MINSIZEREL}>)
set_property(TARGET GTest::gmock PROPERTY INTERFACE_INCLUDE_DIRECTORIES
             $<$<CONFIG:Debug>:${GTest_gmock_INCLUDE_DIRS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gmock_INCLUDE_DIRS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gmock_INCLUDE_DIRS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gmock_INCLUDE_DIRS_MINSIZEREL}>)
set_property(TARGET GTest::gmock PROPERTY INTERFACE_COMPILE_DEFINITIONS
             $<$<CONFIG:Debug>:${GTest_gmock_COMPILE_DEFINITIONS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gmock_COMPILE_DEFINITIONS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gmock_COMPILE_DEFINITIONS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gmock_COMPILE_DEFINITIONS_MINSIZEREL}>)
set_property(TARGET GTest::gmock PROPERTY INTERFACE_COMPILE_OPTIONS
             $<$<CONFIG:Debug>:
                 ${GTest_gmock_COMPILE_OPTIONS_C_DEBUG}
                 ${GTest_gmock_COMPILE_OPTIONS_CXX_DEBUG}>
             $<$<CONFIG:Release>:
                 ${GTest_gmock_COMPILE_OPTIONS_C_RELEASE}
                 ${GTest_gmock_COMPILE_OPTIONS_CXX_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:
                 ${GTest_gmock_COMPILE_OPTIONS_C_RELWITHDEBINFO}
                 ${GTest_gmock_COMPILE_OPTIONS_CXX_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:
                 ${GTest_gmock_COMPILE_OPTIONS_C_MINSIZEREL}
                 ${GTest_gmock_COMPILE_OPTIONS_CXX_MINSIZEREL}>)
set(GTest_gmock_TARGET_PROPERTIES TRUE)

########## COMPONENT gmock_main TARGET PROPERTIES ######################################

set_property(TARGET GTest::gmock_main PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${GTest_gmock_main_LINK_LIBS_DEBUG}
                ${GTest_gmock_main_LINKER_FLAGS_LIST_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gmock_main_LINK_LIBS_RELEASE}
                ${GTest_gmock_main_LINKER_FLAGS_LIST_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gmock_main_LINK_LIBS_RELWITHDEBINFO}
                ${GTest_gmock_main_LINKER_FLAGS_LIST_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gmock_main_LINK_LIBS_MINSIZEREL}
                ${GTest_gmock_main_LINKER_FLAGS_LIST_MINSIZEREL}>)
set_property(TARGET GTest::gmock_main PROPERTY INTERFACE_INCLUDE_DIRECTORIES
             $<$<CONFIG:Debug>:${GTest_gmock_main_INCLUDE_DIRS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gmock_main_INCLUDE_DIRS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gmock_main_INCLUDE_DIRS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gmock_main_INCLUDE_DIRS_MINSIZEREL}>)
set_property(TARGET GTest::gmock_main PROPERTY INTERFACE_COMPILE_DEFINITIONS
             $<$<CONFIG:Debug>:${GTest_gmock_main_COMPILE_DEFINITIONS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gmock_main_COMPILE_DEFINITIONS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gmock_main_COMPILE_DEFINITIONS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gmock_main_COMPILE_DEFINITIONS_MINSIZEREL}>)
set_property(TARGET GTest::gmock_main PROPERTY INTERFACE_COMPILE_OPTIONS
             $<$<CONFIG:Debug>:
                 ${GTest_gmock_main_COMPILE_OPTIONS_C_DEBUG}
                 ${GTest_gmock_main_COMPILE_OPTIONS_CXX_DEBUG}>
             $<$<CONFIG:Release>:
                 ${GTest_gmock_main_COMPILE_OPTIONS_C_RELEASE}
                 ${GTest_gmock_main_COMPILE_OPTIONS_CXX_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:
                 ${GTest_gmock_main_COMPILE_OPTIONS_C_RELWITHDEBINFO}
                 ${GTest_gmock_main_COMPILE_OPTIONS_CXX_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:
                 ${GTest_gmock_main_COMPILE_OPTIONS_C_MINSIZEREL}
                 ${GTest_gmock_main_COMPILE_OPTIONS_CXX_MINSIZEREL}>)
set(GTest_gmock_main_TARGET_PROPERTIES TRUE)

########## COMPONENT gtest_main TARGET PROPERTIES ######################################

set_property(TARGET GTest::gtest_main PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${GTest_gtest_main_LINK_LIBS_DEBUG}
                ${GTest_gtest_main_LINKER_FLAGS_LIST_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gtest_main_LINK_LIBS_RELEASE}
                ${GTest_gtest_main_LINKER_FLAGS_LIST_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gtest_main_LINK_LIBS_RELWITHDEBINFO}
                ${GTest_gtest_main_LINKER_FLAGS_LIST_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gtest_main_LINK_LIBS_MINSIZEREL}
                ${GTest_gtest_main_LINKER_FLAGS_LIST_MINSIZEREL}>)
set_property(TARGET GTest::gtest_main PROPERTY INTERFACE_INCLUDE_DIRECTORIES
             $<$<CONFIG:Debug>:${GTest_gtest_main_INCLUDE_DIRS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gtest_main_INCLUDE_DIRS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gtest_main_INCLUDE_DIRS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gtest_main_INCLUDE_DIRS_MINSIZEREL}>)
set_property(TARGET GTest::gtest_main PROPERTY INTERFACE_COMPILE_DEFINITIONS
             $<$<CONFIG:Debug>:${GTest_gtest_main_COMPILE_DEFINITIONS_DEBUG}>
             $<$<CONFIG:Release>:${GTest_gtest_main_COMPILE_DEFINITIONS_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:${GTest_gtest_main_COMPILE_DEFINITIONS_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:${GTest_gtest_main_COMPILE_DEFINITIONS_MINSIZEREL}>)
set_property(TARGET GTest::gtest_main PROPERTY INTERFACE_COMPILE_OPTIONS
             $<$<CONFIG:Debug>:
                 ${GTest_gtest_main_COMPILE_OPTIONS_C_DEBUG}
                 ${GTest_gtest_main_COMPILE_OPTIONS_CXX_DEBUG}>
             $<$<CONFIG:Release>:
                 ${GTest_gtest_main_COMPILE_OPTIONS_C_RELEASE}
                 ${GTest_gtest_main_COMPILE_OPTIONS_CXX_RELEASE}>
             $<$<CONFIG:RelWithDebInfo>:
                 ${GTest_gtest_main_COMPILE_OPTIONS_C_RELWITHDEBINFO}
                 ${GTest_gtest_main_COMPILE_OPTIONS_CXX_RELWITHDEBINFO}>
             $<$<CONFIG:MinSizeRel>:
                 ${GTest_gtest_main_COMPILE_OPTIONS_C_MINSIZEREL}
                 ${GTest_gtest_main_COMPILE_OPTIONS_CXX_MINSIZEREL}>)
set(GTest_gtest_main_TARGET_PROPERTIES TRUE)

########## GLOBAL TARGET PROPERTIES #########################################################

if(NOT GTest_GTest_TARGET_PROPERTIES)
    set_property(TARGET GTest::GTest APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${GTest_COMPONENTS_DEBUG}>
                 $<$<CONFIG:Release>:${GTest_COMPONENTS_RELEASE}>
                 $<$<CONFIG:RelWithDebInfo>:${GTest_COMPONENTS_RELWITHDEBINFO}>
                 $<$<CONFIG:MinSizeRel>:${GTest_COMPONENTS_MINSIZEREL}>)
endif()

########## BUILD MODULES ####################################################################
#############################################################################################

########## COMPONENT gtest BUILD MODULES ##########################################

foreach(_BUILD_MODULE_PATH ${GTest_gtest_BUILD_MODULES_PATHS_DEBUG})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gtest_BUILD_MODULES_PATHS_RELEASE})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gtest_BUILD_MODULES_PATHS_RELWITHDEBINFO})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gtest_BUILD_MODULES_PATHS_MINSIZEREL})
    include(${_BUILD_MODULE_PATH})
endforeach()

########## COMPONENT gmock BUILD MODULES ##########################################

foreach(_BUILD_MODULE_PATH ${GTest_gmock_BUILD_MODULES_PATHS_DEBUG})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gmock_BUILD_MODULES_PATHS_RELEASE})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gmock_BUILD_MODULES_PATHS_RELWITHDEBINFO})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gmock_BUILD_MODULES_PATHS_MINSIZEREL})
    include(${_BUILD_MODULE_PATH})
endforeach()

########## COMPONENT gmock_main BUILD MODULES ##########################################

foreach(_BUILD_MODULE_PATH ${GTest_gmock_main_BUILD_MODULES_PATHS_DEBUG})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gmock_main_BUILD_MODULES_PATHS_RELEASE})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gmock_main_BUILD_MODULES_PATHS_RELWITHDEBINFO})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gmock_main_BUILD_MODULES_PATHS_MINSIZEREL})
    include(${_BUILD_MODULE_PATH})
endforeach()

########## COMPONENT gtest_main BUILD MODULES ##########################################

foreach(_BUILD_MODULE_PATH ${GTest_gtest_main_BUILD_MODULES_PATHS_DEBUG})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gtest_main_BUILD_MODULES_PATHS_RELEASE})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gtest_main_BUILD_MODULES_PATHS_RELWITHDEBINFO})
    include(${_BUILD_MODULE_PATH})
endforeach()

foreach(_BUILD_MODULE_PATH ${GTest_gtest_main_BUILD_MODULES_PATHS_MINSIZEREL})
    include(${_BUILD_MODULE_PATH})
endforeach()