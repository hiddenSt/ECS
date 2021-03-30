#ifndef ECS_TESTS_TEST_UTILITY_TEST_COMPONENT_TYPE_2_HPP_
#define ECS_TESTS_TEST_UTILITY_TEST_COMPONENT_TYPE_2_HPP_

#include <string>

#include <ecs/component/component_type.hpp>

namespace tests {
namespace utility {

struct TestComponentType2 : public ecs::component::ComponentType<TestComponentType2> {
  explicit TestComponentType2()
      : field_int(1), field_double(4.9), field_string("string_example") {
  }

  explicit TestComponentType2(int field_int, double field_double, std::string field_string)
      : field_int(field_int), field_double(field_double), field_string(field_string) {
  }

  bool operator==(const TestComponentType2& other) const {
    if (field_int != other.field_int) {
      return false;
    }

    if (field_double != other.field_double) {
      return false;
    }

    if (field_string != other.field_string) {
      return false;
    }

    return true;
  }

  int field_int;
  double field_double;
  std::string field_string;
};

}  // namespace utility
}  // namespace tests

#endif  // ECS_TESTS_TEST_UTILITY_TEST_COMPONENT_TYPE_2_HPP_
