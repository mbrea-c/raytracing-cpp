add_library (Rays light.h light.cpp object.h object.cpp plane.h plane.cpp RGB.h RGB.cpp sphere.h sphere.cpp vector.h vector.cpp)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (Rays PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

