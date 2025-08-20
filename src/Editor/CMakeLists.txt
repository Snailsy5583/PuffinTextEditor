cmake_minimum_required(VERSION 3.25)
project(Editor)

set(CMAKE_CXX_STANDARD 17)

set(_src
        main.cpp
        Editor.cpp
        Editor.h
        Cursor.cpp
        Cursor.h
        Textbox.cpp
        Textbox.h)

add_executable(${PROJECT_NAME} ${_src})

target_link_libraries(${PROJECT_NAME} PRIVATE
        Engine
        freetype
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        ../../vendor/glad/include
        ../../vendor/glfw/include
        ../../vendor/freetype/include
        ../../vendor/stb
        ../../vendor/glm
        ../../libs/
        )

# copy shaders folder and fonts folder
add_custom_command(
        TARGET ${PROJECT_NAME} # Or ALL, if you want it to run always
        POST_BUILD # Or PRE_BUILD, depending on when you need the copy
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/Editor/shaders"
        "${PROJECT_BINARY_DIR}/shaders" # Or ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Copying shaders to build directory"
)
add_custom_command(
        TARGET ${PROJECT_NAME} # Or ALL, if you want it to run always
        POST_BUILD # Or PRE_BUILD, depending on when you need the copy
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/vendor/freetype-gl/freetype-gl/fonts/"
        "${PROJECT_BINARY_DIR}/fonts" # Or ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Copying fonts to build directory"
)
#file(COPY "shaders/"
#        DESTINATION "")
#file(COPY "../../vendor/freetype-gl/freetype-gl/fonts/"
#        DESTINATION "${PROJECT_BINARY_DIR}/fonts")