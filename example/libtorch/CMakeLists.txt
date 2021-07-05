cmake_minimum_required(VERSION 3.2)

project(NNet)

set(CMAKE_PREFIX_PATH /home/vip/archiconda3/envs/torch/lib/python3.6/site-packages/torch/share/cmake)

find_package(PythonInterp REQUIRED)
find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(${PROJECT_NAME} src/main.cpp include/network.h)
include_directories(./include)

target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
