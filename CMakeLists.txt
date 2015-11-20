project(arduino-led-interface)
cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(InterfaceLEDStrip)

#add_subdirectory(PatternGenerator)
#add_subdirectory(arch/rtdbobjects)


