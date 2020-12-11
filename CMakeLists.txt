cmake_minimum_required(VERSION 3.10)

project(ECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -Wall -Wextra")

include_directories(include)

add_subdirectory(libs)
add_subdirectory(tests)

set(HEADERS include/component.hpp
            include/component_type.hpp
            include/components_container.hpp
            include/component_type_container.hpp
            include/components_manager.hpp
            include/component_type_iterator.hpp
            include/component_iterator.hpp
            include/types.hpp
            include/system.hpp
            include/system_manager.hpp)
set(SOURCES
            src/component.cpp
            src/components_container.cpp
            src/components_manager.cpp
            src/system.cpp
            src/system_manager.cpp)

add_library(ECS ${HEADERS} ${SOURCES})
