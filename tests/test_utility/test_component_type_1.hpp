#ifndef ECS_TESTS_TEST_UTILITY_TEST_COMPONENT_TYPE_1_HPP_
#define ECS_TESTS_TEST_UTILITY_TEST_COMPONENT_TYPE_1_HPP_

#include <ecs/component/component_type.hpp>

namespace tests {
namespace utility {

class TestComponentType1 : public ecs::component::ComponentType<TestComponentType1> {
 public:
  explicit TestComponentType1()
      : field_1(1), field_2(2), field_3(3.0) {
  }

  explicit TestComponentType1(int field_1, int field_2, double field_3)
      : field_1(field_1), field_2(field_2), field_3(field_3) {
  }

  bool operator==(const TestComponentType1& other) const noexcept {
    if (field_1 != other.field_1) {
      return false;
    }

    if (field_2 != other.field_2) {
      return false;
    }

    if (field_3 != other.field_3) {
      return false;
    }

    return true;
  }
 public:
  int field_1;
  int field_2;
  double field_3;
};

}  // namespace utility
}  // namespace tests

#endif  // ECS_TESTS_TEST_UTILITY_TEST_COMPONENT_TYPE_1_HPP_
