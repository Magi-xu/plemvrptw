cmake_minimum_required(VERSION 3.27)
project(plemvrptw)

set(CMAKE_CXX_STANDARD 20)

set(Torch_DIR libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)
INCLUDE_DIRECTORIES(${TORCH_INCLUDE_DIRS})

set(LIB_SRC
    src/MLP.cpp
    src/Problem.cpp
    src/Customer.cpp
    src/Route.cpp
    src/Solution.cpp
    src/util.cpp
    src/EA.cpp
)

add_library(plemvrptw_lib SHARED ${LIB_SRC})

set(LIBS
    plemvrptw_lib
    ${TORCH_LIBRARIES}
)

add_executable(plemvrptw main.cpp)

target_link_libraries(plemvrptw ${LIBS})
