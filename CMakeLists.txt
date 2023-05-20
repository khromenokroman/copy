cmake_minimum_required(VERSION 3.5)

project(copy)

add_executable(copy
    copy.cpp
)
set_target_properties(copy PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)