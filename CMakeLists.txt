cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE)

project(lvgl C CXX)

# Set the correct FreeRTOS port for your system (e.g., Posix for WSL)
set(FREERTOS_PORT GCC_POSIX CACHE STRING "Port for FreeRTOS on Posix environment")

# option(TEST "Build Unity test executable instead of normal app" OFF)
option(UNIT_TEST_FLAG "Build GTest executable instead of normal app" ON)
# Unit testing with Unity
if(UNIT_TEST_FLAG)
    # message(STATUS "Unity test is enabled")
    message(STATUS "GTest is enabled")
    add_definitions(-DUNIT_TEST_FLAG=1)
else()
    # message(STATUS "Unity test is disabled")
    message(STATUS "GTest is disabled")
    add_definitions(-DUNIT_TEST_FLAG=0)
endif()

option(USE_FREERTOS "Enable FreeRTOS" OFF) # Turn this on to enable FreeRTOS

if(USE_FREERTOS)
    message(STATUS "FreeRTOS is enabled")

    # FreeRTOS integration when USE_FREERTOS is enabled
    add_library(freertos_config INTERFACE)
    target_include_directories(freertos_config SYSTEM INTERFACE ${PROJECT_SOURCE_DIR}/config)
    target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)

    # Add FreeRTOS as a subdirectory
    add_subdirectory(FreeRTOS)

    # FreeRTOS-specific include directories
    include_directories(${PROJECT_SOURCE_DIR}/FreeRTOS/include)
    include_directories(${PROJECT_SOURCE_DIR}/FreeRTOS/portable/ThirdParty/GCC/Posix)
    include_directories(${PROJECT_SOURCE_DIR}/config)

    # Add FreeRTOS sources
    file(GLOB FREERTOS_SOURCES
        "${PROJECT_SOURCE_DIR}/FreeRTOS/*.c"
        "${PROJECT_SOURCE_DIR}/FreeRTOS/portable/MemMang/heap_4.c"
        "${PROJECT_SOURCE_DIR}/FreeRTOS/portable/ThirdParty/GCC/Posix/*.c"
    )
else()
    message(STATUS "FreeRTOS is disabled")
    set(FREERTOS_SOURCES "")  # No FreeRTOS sources if FreeRTOS is disabled
endif()

# ----------------------------------------------------------------------------------------------
if(UNIT_TEST_FLAG)
    # googletest include, code from gtest official repository on github
    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()
# ----------------------------------------------------------------------------------------------

# Main include files of the project
include_directories(${PROJECT_SOURCE_DIR}/main/inc)

# Disable LVGL demos/examples and ThorVG
set(LVGL_BUILD_DEMOS OFF CACHE BOOL "Disable LVGL demos" FORCE)
set(LVGL_BUILD_EXAMPLES OFF CACHE BOOL "Disable LVGL examples" FORCE)
# set(LV_USE_TORVG OFF CACHE BOOL "Disable ThorVG" FORCE)

# Define options for LVGL with default values (OFF)
option(LV_USE_DRAW_SDL "Use SDL draw unit" OFF)
option(LV_USE_LIBPNG "Use libpng to decode PNG" ON)
option(LV_USE_LIBJPEG_TURBO "Use libjpeg turbo to decode JPEG" ON)
option(LV_USE_FFMPEG "Use libffmpeg to display video using lv_ffmpeg" OFF)
option(LV_USE_FREETYPE "Use freetype library" OFF)

# Set C and C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output path for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

# Find and include SDL2 library
set(SDL2_DIR "C:/northh/repos/vcpkg/installed/x64-mingw-dynamic/share/sdl2")
find_package(SDL2 REQUIRED)

# Add compile definitions based on the selected options
add_compile_definitions($<$<BOOL:${LV_USE_DRAW_SDL}>:LV_USE_DRAW_SDL=1>)
add_compile_definitions($<$<BOOL:${LV_USE_LIBPNG}>:LV_USE_LIBPNG=1>)
add_compile_definitions($<$<BOOL:${LV_USE_LIBJPEG_TURBO}>:LV_USE_LIBJPEG_TURBO=1>)
add_compile_definitions($<$<BOOL:${LV_USE_FFMPEG}>:LV_USE_FFMPEG=1>)

# Add LVGL subdirectory
add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
# Add GUI subdirectories, added to libs list further down the code
add_subdirectory(src/gui_main_screen)

# Normal app sources
set(MAIN_SOURCES 
    src/mouse_cursor_icon.c 
    src/hal/hal.c 
    src/testcode.c
)

# Googletest test sources
set(TEST_SOURCES
    src/mouse_cursor_icon.c 
    src/hal/hal.c 
    src/testcode.c
    # unity_test/unity.c
    # unity_test/test/test_main.c
    # unity_test/test/test_main_Runner.c
    lvgl/src/others/test/lv_test_display.c
    lvgl/src/others/test/lv_test_indev.c
    lvgl/src/others/test/lv_test_screenshot_compare.c
)

# set(MAIN_LIBS lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES})
# set(TEST_LIBS lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES})
if(UNIT_TEST_FLAG)
    set(TEST_LIBS lvgl lvgl::thorvg ${SDL2_LIBRARIES} gui_main_screen)
else()
    set(MAIN_LIBS lvgl lvgl::thorvg ${SDL2_LIBRARIES} gui_main_screen)
endif()

# Create the main executable, depending on the FreeRTOS option
if(USE_FREERTOS)
    list(APPEND MAIN_SOURCES src/freertos_main.c src/freertos/freertos_posix_port.c ${FREERTOS_SOURCES})
    list(APPEND MAIN_LIBS freertos_config freertos_kernel)
    list(APPEND TEST_LIBS freertos_config freertos_kernel)
else()
    list(APPEND MAIN_SOURCES src/main.c)
    list(APPEND TEST_SOURCES src/main.c)
endif()

if(NOT MSVC)
    list(APPEND MAIN_LIBS m pthread)
    list(APPEND TEST_LIBS m pthread)
endif()

# Conditionally include and link SDL2_image if LV_USE_DRAW_SDL is enabled
if(LV_USE_DRAW_SDL)
    set(CMAKE_TOOLCHAIN_FILE "C:/northh/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain fil")
    find_package(SDL2 REQUIRED)
    set(SDL2_image_DIR "C:/northh/repos/vcpkg/installed/x64-mingw-dynamic/share/SDL2_image")
    find_package(SDL2_image REQUIRED)
    target_include_directories(lvgl PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
    list(APPEND MAIN_LIBS ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
    list(APPEND TEST_LIBS ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()

# Conditionally include and link libpng if LV_USE_LIBPNG is enabled
if(LV_USE_LIBPNG)
    # Ensure vcpkg toolchain file is used (if not already)
    if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "C:/northh/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    endif()
    find_package(PNG REQUIRED)
    if(PNG_FOUND)
        message(STATUS "libpng found: ${PNG_LIBRARIES}")
        target_include_directories(lvgl PUBLIC ${PNG_INCLUDE_DIRS})
        list(APPEND MAIN_LIBS ${PNG_LIBRARIES})
        list(APPEND TEST_LIBS ${PNG_LIBRARIES})
    else()
        message(FATAL_ERROR "libpng not found!")
    endif()
endif()

# Conditionally include and link libjpeg-turbo if LV_USE_LIBJPEG_TURBO is enabled
if(LV_USE_LIBJPEG_TURBO)
    find_package(JPEG REQUIRED)
    target_include_directories(lvgl PUBLIC ${JPEG_INCLUDE_DIRS})
    list(APPEND MAIN_LIBS ${JPEG_LIBRARIES})
    list(APPEND TEST_LIBS ${JPEG_LIBRARIES})
endif()

# Conditionally include and link FFmpeg libraries if LV_USE_FFMPEG is enabled
if(LV_USE_FFMPEG)
    list(APPEND MAIN_LIBS avformat avcodec avutil swscale z)
    list(APPEND TEST_LIBS avformat avcodec avutil swscale z)
endif()

# Conditionally include and link FreeType if LV_USE_FREETYPE is enabled
if(LV_USE_FREETYPE)
    find_package(Freetype REQUIRED)
    target_include_directories(lvgl PUBLIC ${FREETYPE_INCLUDE_DIRS})
    list(APPEND MAIN_LIBS ${FREETYPE_LIBRARIES})
    list(APPEND TEST_LIBS ${FREETYPE_LIBRARIES})
endif()

if(UNIT_TEST_FLAG)
    # NOTHING, everything testrelated is in gtest_units/CMakeLists.txt
else()
    add_executable(main ${MAIN_SOURCES})
    target_compile_definitions(main PRIVATE LV_CONF_INCLUDE_SIMPLE)
    target_link_libraries(main ${MAIN_LIBS})
endif()

# On Windows, GUI applications do not show a console by default,
# which hides log output. This ensures a console is available for logging.
if (WIN32)
    if (MSVC)
        if (UNIT_TEST_FLAG)
            # target_link_options(hello_test PRIVATE "/SUBSYSTEM:CONSOLE")
        else()
            target_link_options(main PRIVATE "/SUBSYSTEM:CONSOLE")
        endif()
    else()
        if (UNIT_TEST_FLAG)
            # target_link_options(hello_test PRIVATE "-mconsole")
        else()
            target_link_options(main PRIVATE "-mconsole")
        endif()
    endif()
endif()

# Apply additional compile options if the build type is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled")

    target_compile_options(lvgl PRIVATE
        -pedantic-errors
        -Wall
        -Wclobbered
        -Wdeprecated
        -Wdouble-promotion
        -Wempty-body
        -Wextra
        -Wformat-security
        -Wmaybe-uninitialized
        # -Wmissing-prototypes
        -Wpointer-arith
        -Wmultichar
        -Wno-pedantic # ignored for now, we convert functions to pointers for properties table.
        -Wreturn-type
        -Wshadow
        -Wshift-negative-value
        -Wsizeof-pointer-memaccess
        -Wtype-limits
        -Wundef
        -Wuninitialized
        -Wunreachable-code
        -Wfloat-conversion
        -Wstrict-aliasing
    )

if (ASAN)
    message(STATUS "AddressSanitizer enabled")

    # Add AddressSanitizer flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
else()
    message(STATUS "AddressSanitizer disabled")
endif()

# RUN GTEST
# Add GTest subdirectories
if(UNIT_TEST_FLAG)
    add_subdirectory(gtest_units)
endif()

endif()