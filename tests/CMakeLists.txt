project(ECS)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${Allocators_SOURCE_DIR}/include)

add_executable(Google_Test_Run
        component_tests.cpp
        components_container_test.cpp
        components_manager_test.cpp
        system_tests.cpp
        systems_manager_test.cpp components_iterator_test.cpp entities_manager_test.cpp)
target_link_libraries(Google_Test_Run gtest gtest_main ECS Allocators)