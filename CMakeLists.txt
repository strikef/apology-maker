cmake_minimum_required (VERSION 3.13)
project(ApologyMaker VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_executable (ApologyMaker src/main_win.cpp)
else()
    add_executable (ApologyMaker src/main_nix.cpp)
endif()
