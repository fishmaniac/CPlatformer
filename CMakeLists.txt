# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.26)

# Set the project name
project(Shooter)

# Find the SDL2 library
find_package(SDL2 REQUIRED)
# Find the SDL2_image library
find_package(SDL2_image REQUIRED)

# Add the SDL2 and SDL2_image header files to the include path
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Add your project executable
add_executable(Shooter main.c structs.c scene.c)

# Link against the SDL2 and SDL2_image libraries
target_link_libraries(Shooter ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
