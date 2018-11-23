cmake_minimum_required (VERSION 2.6)
project (raytracer)


# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (src)
add_subdirectory (include)


add_executable(raytracer src/main.cpp)

target_link_libraries (raytracer LINK_PUBLIC Rays)
