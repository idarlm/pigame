cmake_minimum_required(VERSION 3.5)
project(pigame)

# find sdl2 package
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2-shared)

# add executable
add_executable(pigame pigame.c)

# link to SDL2 library
target_link_libraries(pigame PRIVATE SDL2::SDL2)
