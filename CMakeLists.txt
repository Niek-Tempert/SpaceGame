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

find_package(OpenGL REQUIRED)

set(EXTERN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SpaceGame)

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
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(STB_DIR ${EXTERN_DIR}/stb)
set(GLM_DIR ${EXTERN_DIR}/glm)

set(PROJ_SRC
    ${PROJ_DIR}/SpaceGame.cpp
    ${PROJ_DIR}/debug_panel.h
    ${PROJ_DIR}/models/cube.h
    ${PROJ_DIR}/models/block_cursor.h
    ${PROJ_DIR}/models/cursor.h
    ${PROJ_DIR}/models/monkey.h
    ${PROJ_DIR}/models/skybox.h
    ${PROJ_DIR}/nixelib/nixelib.h
    ${PROJ_DIR}/nixelib/src/hash.h
    ${PROJ_DIR}/nixelib/src/macros.h
    ${PROJ_DIR}/nixelib/src/nixemath.h
    ${PROJ_DIR}/nixelib/src/typedefs.h
    ${PROJ_DIR}/nixelib/src/types/vec2.h
    ${PROJ_DIR}/nixelib/src/types/vec2i.h
    ${PROJ_DIR}/nixelib/src/types/vec3.h
    ${PROJ_DIR}/nixelib/src/types/vec3i.h
    ${PROJ_DIR}/nixelib/src/types/vec4.h
    ${PROJ_DIR}/nixelib/src/types/vec4i.h
    ${PROJ_DIR}/program.h
    ${PROJ_DIR}/utils/file.h
    ${PROJ_DIR}/utils/input.hpp
    ${PROJ_DIR}/utils/mesh_consts.h
    ${PROJ_DIR}/utils/player.h
    ${PROJ_DIR}/voxel/cell/cell_mesher.h
    ${PROJ_DIR}/voxel/cell/physic_rule.h
    ${PROJ_DIR}/voxel/cell/cell_user.h
    ${PROJ_DIR}/voxel/cell/cell.h
    ${PROJ_DIR}/voxel/cell/cell_shape.h
    ${PROJ_DIR}/voxel/chunk.h
    ${PROJ_DIR}/voxel/chunk_mesher.h
    ${PROJ_DIR}/voxel/voxel_register.h
    ${PROJ_DIR}/voxel/voxel.h
    ${PROJ_DIR}/SpaceGame.cpp
    ${PROJ_DIR}/rendering/line_renderable.cpp
    ${PROJ_DIR}/rendering/renderable.cpp
    ${PROJ_DIR}/rendering/shader.cpp
    ${PROJ_DIR}/voxel/chunk.cpp
    ${PROJ_DIR}/voxel/chunk_mesher.cpp
    ${PROJ_DIR}/voxel/voxel.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJ_SRC}
    ${GLAD_SRC}
    ${IMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJ_DIR}
    ${GLAD_INCLUDE_DIR}
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${EXTERN_DIR}/glfw/include
    ${STB_DIR}
    ${GLM_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    ${OPENGL_LIBRARIES}
)

file(COPY ${PROJ_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJ_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    GLAD_GL_IMPLEMENTATION
    GLFW_INCLUDE_NONE
)
