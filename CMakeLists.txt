cmake_minimum_required(VERSION 4.2)
project(Ataxx)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-O1")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG -funroll-loops")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Ataxx main.cpp
        src/ataxx.h
        perft/perft.h
        perft/perftTT.h
        engine/uai.h
        engine/root.h
)
