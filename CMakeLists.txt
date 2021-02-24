cmake_minimum_required(VERSION 3.14)
project(ecs VERSION 1.0)

include(cmake/ClangFormat.cmake)
include(cmake/ClangTidy.cmake)

option(ECS_DEVELOPER "ECS development mode" ON)
option(ECS_TESTS "Enable ECS tests" OFF)

add_subdirectory(third-party)

add_subdirectory(ecs)

if(ECS_TESTS OR ECS_DEVELOPER)
  add_subdirectory(tests)
endif()
