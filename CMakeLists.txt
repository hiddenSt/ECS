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
            include/types.hpp
            include/system.hpp
            include/systems_manager.hpp
            include/system_type.hpp
            include/components_look_up_table.hpp
            include/utility/map_look_up_table.hpp
            include/entity_manager.hpp
            include/entitys_id_container.hpp
            include/engine.hpp
            include/components_iterator.hpp
            include/utility/map_components_iterator.hpp)
set(SOURCES
            src/component.cpp
            src/components_container.cpp
            src/utility/map_look_up_table.cpp
            src/entity_manager.cpp
            src/engine.cpp
            src/utility/map_components_iterator.cpp
        src/system.cpp src/systems_manager.cpp src/components_manager.cpp)

add_library(ECS ${HEADERS} ${SOURCES})
