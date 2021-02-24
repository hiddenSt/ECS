get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.hpp)

add_library(ecs STATIC ${LIB_CXX_SOURCES} ${LIB_HEADERS})
target_include_directories(ecs PRIVATE ${LIB_INCLUDE_PATH} ${allocators_SOURCE_DIR})
target_link_libraries(ecs PRIVATE allocators)

# Linters

if(ECS_DEVELOPER)

  if(CLANG_FORMAT_TOOL)
    add_clang_format_target(ecs_clang_format ${CMAKE_CURRENT_SOURCE_DIR} ${LIB_HEADERS} ${LIB_CXX_SOURCES})
  endif()

  if(CLANG_TIDY_TOOL)
    add_clang_tidy_target(ecs_clang_tidy ${CMAKE_CURRENT_SOURCE_DIR} ${LIB_INCLUDE_PATH} ${LIB_HEADERS} ${LIB_CXX_SOURCES})
  endif()

endif()