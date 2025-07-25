cmake_minimum_required(VERSION 3.30)
project(SandPile)

set(CMAKE_CXX_STANDARD 26)

include_directories(src)

add_executable(SandPile main.cpp
        src/ParseArguments.h
        src/ParseArguments.cpp
        src/bmp.cpp
        src/bmp.h
        src/sandpile.h
        src/sandpile.cpp
        src/tsv.cpp
        src/tsv.h)
