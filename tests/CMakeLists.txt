project(ECS)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Test_Run component_tests.cpp component_tests.cpp)
target_link_libraries(Google_Test_Run gtest gtest_main ECS)