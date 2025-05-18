cmake_minimum_required(VERSION 3.15)
project(SDL2Project C)

# Encontre o SDL2 instalado via Homebrew
set(SDL2_PATH /opt/homebrew/Cellar/sdl2/2.32.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)

# Adicione os includes e libs manualmente
include_directories(${SDL2_PATH}/include)
link_directories(${SDL2_PATH}/lib)

# Adicione o seu arquivo fonte
add_executable(main main.c)

# Link com a SDL2
target_link_libraries(main SDL2)
