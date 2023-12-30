cmake_minimum_required(VERSION 3.27)
project(plemvrptw)

set(CMAKE_CXX_STANDARD 20)

set(Torch_DIR libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)

add_executable(plemvrptw main.cpp)

target_link_libraries(plemvrptw ${TORCH_LIBRARIES})
