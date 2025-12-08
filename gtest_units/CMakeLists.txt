cmake_minimum_required(VERSION 3.14)

# see if headers are included
message(STATUS "Configure gtest_units")

# header files dont need to be named for cmake, just for overview
set(GTEST_SOURCES
    gtest_gui_test/src/gtest_main_menu.cpp
)

# googletest enableing
enable_testing()

# create testexecutable | and this could then be test1
add_executable(gtest_runner ${GTEST_SOURCES}) # RENAME FOR FUTURE TESTING

# expose lvgl includes to this target so headers can use "lvgl.h"
target_link_libraries(gtest_runner # RENAME FOR FUTURE TESTING
    PRIVATE
        GTest::gtest_main
        ${TEST_LIBS}
)

# naming for easier use in main CMakeLists.txt
target_include_directories(gtest_runner # RENAME FOR FUTURE TESTING
    PRIVATE
        ${PROJECT_SOURCE_DIR} 
        ${CMAKE_CURRENT_SOURCE_DIR}
)
