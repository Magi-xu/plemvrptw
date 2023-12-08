cmake_minimum_required(VERSION 3.25)
project(plemvrptw)

set(CMAKE_CXX_STANDARD 23)

set(Torch_DIR /Users/magi/libtorch/share/cmake/Torch)

find_package(Torch REQUIRED)

add_executable(
        plemvrptw main.cpp
        src/Problem.cpp
        src/Problem.h
        src/Customer.cpp
        src/Customer.h
        src/Route.cpp
        src/Route.h
        src/Solution.cpp
        src/Solution.h
        src/MLP.h src/EA.cpp src/EA.h src/plemvrptw.h)

target_link_libraries(plemvrptw ${TORCH_LIBRARIES})