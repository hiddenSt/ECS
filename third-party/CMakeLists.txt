include(FetchContent)

# Google Test

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)
FetchContent_GetProperties(googletest)

if (${googletest}_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()



# Allocators

FetchContent_Declare(
  allocators
  GIT_REPOSITORY https://github.com/hiddenSt/Allocators.git
  GIT_TAG master
)
FetchContent_GetProperties(allocators)

if (NOT ${allocators}_POPULATED)
  FetchContent_Populate(allocators)
  add_subdirectory(${allocators_SOURCE_DIR} ${allocators_BINARY_DIR})
endif()