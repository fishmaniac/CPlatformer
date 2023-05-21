cmake_minimum_required(VERSION 3.26)

project(Shooter)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Shooter main.c entity.c scene.c textures.c)

target_link_libraries(Shooter ${SDL2_LIBRARIES})
