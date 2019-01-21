cmake_minimum_required (VERSION 2.6)
project (raytracer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.

# Recurse into the "src" subdirectory. 
add_subdirectory (src)


add_executable(raytracer src/main.cpp)

target_link_libraries (raytracer LINK_PUBLIC Rays)
