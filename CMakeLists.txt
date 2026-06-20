cmake_minimum_required(VERSION 3.15)
project(
    SpaceGame
    DESCRIPTION "SpaceGame demo made with OpenGL."
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Vulkan REQUIRED)

set(EXTERN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${EXTERN_DIR}/glfw)

set(GLAD_INCLUDE_DIR ${EXTERN_DIR}/glad/include)
set(GLAD_SRC ${EXTERN_DIR}/glad/src/glad.c)

set(IMGUI_DIR ${EXTERN_DIR}/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)

set(STB_DIR ${EXTERN_DIR}/stb)
set(GLM_DIR ${EXTERN_DIR}/glm)

set(PROJ_SRC
    ${PROJ_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJ_SRC}
    ${GLAD_SRC}
    ${IMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJ_DIR}
    ${Vulkan_INCLUDE_DIRS}
    ${GLAD_INCLUDE_DIR}
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${EXTERN_DIR}/glfw/include
    ${STB_DIR}
    ${GLM_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Vulkan_LIBRARIES}
    glfw
)

file(GLOB_RECURSE SHADER_FILES "src/shaders/*")
file(GLOB_RECURSE ASSET_FILES "src/assets/*")

target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    GLAD_GL_IMPLEMENTATION
    GLFW_INCLUDE_NONE
    # GLFW_INCLUDE_VULKAN
)
