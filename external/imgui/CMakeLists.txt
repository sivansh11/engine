set(IMGUI_DIR imgui)

file(GLOB SRC_FILES ${IMGUI_DIR}/*cpp)

set(BACKENDS ${IMGUI_DIR}/backends)

add_compile_options(-fPIC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${IMGUI_DIR})
# include_directories(backends)

set(BACKEND_SRC_FILES 
    ${BACKENDS}/imgui_impl_opengl3.cpp
    ${BACKENDS}/imgui_impl_glfw.cpp
)

# message(STATUS "foo include dir: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "foo include dir: ${THIRDPARTY_PATH}")

add_library(imgui ${SRC_FILES} ${BACKEND_SRC_FILES})



