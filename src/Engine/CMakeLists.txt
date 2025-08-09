cmake_minimum_required(VERSION 3.25)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(__src
        Application.h
        Application.cpp
        Layer.h
        Layer.cpp
        Renderer.h
        Renderer.cpp
        Shader.h
        Shader.cpp
        Window.h
        Window.cpp

        stb.cpp
        GameObject.cpp GameObject.h Component.h Component.cpp)

set(__src__Events
        Events/Events.h
        Events/MouseEvents.h
        Events/WindowEvents.h
)

add_library(${PROJECT_NAME} ${__src} ${__src__Events})

################################# linking ######################################
target_link_libraries(${PROJECT_NAME}
        glfw
        glad
        ImGui
        opengl32
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ../../vendor/glad/include
        ../../vendor/glfw/include
        ../../vendor/imgui
        ../../vendor/stb
)