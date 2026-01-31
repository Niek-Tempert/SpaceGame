cmake_minimum_required(VERSION 3.15)
project(
    SpaceGame
    DESCRIPTION "SpaceGame demo made with OpenGL."
    LANGUAGES C CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform-specific settings
if(WIN32)
    add_definitions(-DWIN32)
endif()

# Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_subdirectory(extern/glfw)

include_directories(
    extern/glad/include/
    extern/glfw/include/
    extern/glm/
    extern/stb/
    extern/imgui/
    extern/imgui/backends/
)

include_directories(
    ${CMAKE_SOURCE_DIR}/SpaceGame
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(GLAD_SOURCES extern/glad/src/glad.c)

set(GLFW_SOURCES
    extern/glfw/src/context.c
    extern/glfw/src/init.c
    extern/glfw/src/input.c
    extern/glfw/src/monitor.c
    extern/glfw/src/vulkan.c
    extern/glfw/src/window.c
    extern/glfw/src/platform.c
    extern/glfw/src/null_*.c
)

set(IMGUI_SOURCES
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
)

set(STB_SOURCES
    extern/stb/stb_image.c
)

# Source files
set(SOURCES
    SpaceGame/SpaceGame.cpp
    SpaceGame/debug_panel.h
    SpaceGame/models/cube.h
    SpaceGame/models/block_cursor.h
    SpaceGame/models/cursor.h
    SpaceGame/models/monkey.h
    SpaceGame/models/skybox.h
    SpaceGame/nixelib/nixelib.h
    SpaceGame/nixelib/src/hash.h
    SpaceGame/nixelib/src/macros.h
    SpaceGame/nixelib/src/nixemath.h
    SpaceGame/nixelib/src/typedefs.h
    SpaceGame/nixelib/src/types/vec2.h
    SpaceGame/nixelib/src/types/vec2i.h
    SpaceGame/nixelib/src/types/vec3.h
    SpaceGame/nixelib/src/types/vec3i.h
    SpaceGame/nixelib/src/types/vec4.h
    SpaceGame/nixelib/src/types/vec4i.h
    SpaceGame/program.h
    SpaceGame/utils/file.h
    SpaceGame/utils/input.hpp
    SpaceGame/utils/mesh_consts.h
    SpaceGame/utils/player.h
    SpaceGame/voxel/cell/cell_mesher.h
    SpaceGame/voxel/cell/physic_rule.h
    SpaceGame/voxel/cell/cell_user.h
    SpaceGame/voxel/cell/cell.h
    SpaceGame/voxel/cell/cell_shape.h
    SpaceGame/voxel/chunk.h
    SpaceGame/voxel/chunk_mesher.h
    SpaceGame/voxel/voxel_register.h
    SpaceGame/voxel/voxel.h
)

set(SOURCE_FILES
    SpaceGame/SpaceGame.cpp
    SpaceGame/rendering/line_renderable.cpp
    SpaceGame/rendering/renderable.cpp
    SpaceGame/rendering/shader.cpp
    SpaceGame/voxel/chunk.cpp
    SpaceGame/voxel/chunk_mesher.cpp
    SpaceGame/voxel/voxel.cpp
)

add_library(glad STATIC ${GLAD_SOURCES})
# add_library(glfw STATIC ${GLFW_SOURCES})
# add_library(stb STATIC ${STB_SOURCES})

# Add the executable
add_executable(SpaceGame ${SOURCES} ${SOURCE_FILES} ${IMGUI_SOURCES})

find_package(OpenGL REQUIRED)

target_link_libraries(SpaceGame 
    glfw 
    glad 
    opengl32
)

# Windows libraries
if(WIN32)
    target_link_libraries(SpaceGame
        kernel32
        user32
        gdi32
        winspool
        shell32
        ole32
        oleaut32
        uuid
        comdlg32
        advapi32
    )
endif()

# Compiler options for different configurations
target_compile_options(SpaceGame PRIVATE
    $<$<CONFIG:Debug>:-O0 -g>
    $<$<CONFIG:Release>:-O3>
)

# Preprocessor definitions
target_compile_definitions(SpaceGame PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    _CONSOLE
)

# Copy shaders and assets to build directory
file(GLOB_RECURSE SHADER_FILES "SpaceGame/shaders/*")
file(GLOB_RECURSE ASSET_FILES "SpaceGame/assets/*")

# Copy files to build directory
add_custom_command(TARGET SpaceGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/SpaceGame/shaders
        $<TARGET_FILE_DIR:SpaceGame>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/SpaceGame/assets
        $<TARGET_FILE_DIR:SpaceGame>/assets
)
