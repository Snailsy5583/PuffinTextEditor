cmake_minimum_required(VERSION 3.25)
project(PuffinTextEditor)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

add_library(freetype STATIC IMPORTED GLOBAL)
set_target_properties(freetype PROPERTIES
        IMPORTED_LOCATION_DEBUG
        "${CMAKE_SOURCE_DIR}/vendor/freetype/objs/Win32/Debug Static/freetype.lib"
        IMPORTED_LOCATION_RELEASE
        "${CMAKE_SOURCE_DIR}/vendor/freetype/objs/Win32/Release Static/freetype.lib"
        )

add_subdirectory(libs/Engine)
add_subdirectory(src/Editor)
