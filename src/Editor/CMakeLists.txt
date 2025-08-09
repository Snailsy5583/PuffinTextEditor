cmake_minimum_required(VERSION 3.25)
project(Editor)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Engine
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ../../vendor/glad/include
        ../../vendor/glfw/include
        ../
        )