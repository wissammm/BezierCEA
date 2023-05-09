

if(NOT TARGET GTest::gtest)
    add_library(GTest::gtest INTERFACE IMPORTED)
endif()

if(NOT TARGET GTest::gmock)
    add_library(GTest::gmock INTERFACE IMPORTED)
endif()

if(NOT TARGET GTest::gmock_main)
    add_library(GTest::gmock_main INTERFACE IMPORTED)
endif()

if(NOT TARGET GTest::gtest_main)
    add_library(GTest::gtest_main INTERFACE IMPORTED)
endif()

if(NOT TARGET GTest::GTest)
    add_library(GTest::GTest INTERFACE IMPORTED)
endif()

# Load the debug and release library finders
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB CONFIG_FILES "${_DIR}/GTestTarget-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()

if(GTest_FIND_COMPONENTS)
    foreach(_FIND_COMPONENT ${GTest_FIND_COMPONENTS})
        list(FIND GTest_COMPONENTS_RELEASE "GTest::${_FIND_COMPONENT}" _index)
        if(${_index} EQUAL -1)
            conan_message(FATAL_ERROR "Conan: Component '${_FIND_COMPONENT}' NOT found in package 'GTest'")
        else()
            conan_message(STATUS "Conan: Component '${_FIND_COMPONENT}' found in package 'GTest'")
        endif()
    endforeach()
endif()