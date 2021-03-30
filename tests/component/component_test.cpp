#include <gtest/gtest.h>

#include <ecs/component/component_type.hpp>
#include <tests/test_utility/test_component_type_1.hpp>
#include <tests/test_utility/test_component_type_2.hpp>

TEST(ComponentTest, ComponentTypeGetsId) {
  ASSERT_EQ(tests::utility::TestComponentType1::StaticGetComponentTypeId(), 1);
}

TEST(ComponentTest, ComponentTypeInstanceReturnsCorrectId) {
  tests::utility::TestComponentType1 comp1{};
  ASSERT_EQ(tests::utility::TestComponentType1::StaticGetComponentTypeId(),
            comp1.GetComponentTypeId());
}

TEST(ComponentTest, GeneratesCorrectUniqueIdForEveryComponentType) {
  std::size_t comp_1_id = tests::utility::TestComponentType1::StaticGetComponentTypeId();
  std::size_t comp_2_id = tests::utility::TestComponentType2::StaticGetComponentTypeId();
  ASSERT_EQ(comp_2_id - comp_1_id, 1);
}

TEST(ComponentTest, ComponentHasDefaultEntityIdEqualsTo0) {
  tests::utility::TestComponentType1 comp1{};
  std::size_t default_entity_id_value = 0;
  ASSERT_EQ(comp1.GetEntityId(), default_entity_id_value);
}

TEST(ComponentTest, CanChangeComponentEntityId) {
  tests::utility::TestComponentType1 comp1{};
  std::size_t entity_id = 3;
  comp1.SetEntityId(entity_id);
  ASSERT_EQ(comp1.GetEntityId(), entity_id);
}
