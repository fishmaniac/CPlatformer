cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Shooter main.c scene.c textures.c entity.c)

target_link_libraries(Shooter ${SDL2_LIBRARIES})