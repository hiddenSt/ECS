cmake_minimum_required(VERSION 3.15)

project(ECS)

set(CMAKE_CXX_STANDARD 17)

add_library(ECS i_component.cpp i_component.hpp component.hpp i_component_container.hpp types.hpp components_manger.cpp components_manger.hpp)
