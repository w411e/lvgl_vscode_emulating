cmake_minimum_required(VERSION 3.14)

project(gui_main_screen)

# see if headers are included
message(STATUS "Including Main Screen GUI")

# header files dont need to be named for cmake, just for overview
set(MAIN_SCREEN_SOURCES
    src/main_screen.cpp
    src/main_screen_handlers.cpp
    src/main_screen_c_api.cpp
)

# combining all sources into one "name"
add_library(gui_main_screen STATIC ${MAIN_SCREEN_SOURCES})

# expose lvgl includes to this target so headers can use "lvgl.h"
target_link_libraries(gui_main_screen PUBLIC lvgl)

# naming for easier use in main CMakeLists.txt
target_include_directories(gui_main_screen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})