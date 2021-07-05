cmake_minimum_required(VERSION 3.2)

project(torchcv)

set(CMAKE_PREFIX_PATH /home/vip/archiconda3/envs/torch/lib/python3.6/site-packages/torch/share/cmake)
set(CMAKE_INSTALL_PREFIX /usr/local)
set(CMAKE_BUILD_TYPE Release)
set(OPENCV_EXTRA_MODULES_PATH /home/vip/opencv_contrib/modules)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(PythonInterp REQUIRED)
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(# ./include
    ${OpenCV_INCLUDE_DIRS}
)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
