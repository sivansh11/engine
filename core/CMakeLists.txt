cmake_minimum_required(VERSION 3.0)
project(core)

file(GLOB SRC_FILES src/*.cpp)

add_definitions(-fPIC)

add_library(core ${SRC_FILES})
include_directories(core 
    PUBLIC external/imgui/imgui
)
target_include_directories(core 
    PUBLIC include/
    PUBLIC external/imgui/imgui
)
target_link_libraries(core
    stdc++fs
    dl
)