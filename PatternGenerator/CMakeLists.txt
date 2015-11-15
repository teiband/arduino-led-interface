project(PatternGenerator)
cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(.)

add_executable(pattern_generator
        PatternGenerator.cpp
        main.cpp
)

