cmake_minimum_required(VERSION 3.10)

project(app)

file(GLOB PROJECT_SRC src/*.cpp)

include_directories(${PROJECT_NAME}
    include
)

add_definitions(-DLINUX)
add_definitions(-DDEBUG_INFO)


add_subdirectory(core)
add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/imgui)

# add_definitions(-DLINUX)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC include
)

target_link_libraries(${PROJECT_NAME}
    core
)