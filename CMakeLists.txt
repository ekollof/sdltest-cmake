cmake_minimum_required(VERSION 2.8)
project(SDLtest)
add_executable(sdltest main.c assets.c events.c globals.c init.c keyboard.c levels.c main.c video.c window.c )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CC clang)

# Find stuff
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

install(TARGETS sdltest DESTINATION bin)
target_link_libraries(sdltest ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})
