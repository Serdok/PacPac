cmake_minimum_required(VERSION 3.16)
project(PacPac)

set(CMAKE_CXX_STANDARD 20)

# Setup all external codes
add_subdirectory(vendor)

# Setup the main game library
add_subdirectory(PacPac)

# Setup the game with graphics
add_subdirectory(Graphics)