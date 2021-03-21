#include <gtest/gtest.h>

#include <ecs/component/component_type.hpp>

class Component1 : public ecs::component::ComponentType<Component1> {
  int a;
  float b;
};

class Component2 : public ecs::component::ComponentType<Component2> {
  int a;
  float b;
};

TEST(ComponentTest, ComponentTypeGetsId) {
  ASSERT_EQ(Component1::StaticGetComponentTypeId(), 1);
}

TEST(ComponentTest, ComponentTypeInstanceReturnsCorrectId) {
  Component1 comp1{};
  ASSERT_EQ(Component1::StaticGetComponentTypeId(), comp1.GetComponentTypeId());
}

TEST(ComponentTest, GeneratesCorrectUniqueIdForEveryComponentType) {
  std::size_t comp_1_id = Component1::StaticGetComponentTypeId();
  std::size_t comp_2_id = Component2::StaticGetComponentTypeId();
  ASSERT_EQ(comp_2_id - comp_1_id, 1);
}

TEST(ComponentTest, ComponentHasDefaultEntityIdEqualsTo0) {
  Component1 comp1{};
  std::size_t default_entity_id_value = 0;
  ASSERT_EQ(comp1.GetEntityId(), default_entity_id_value);
}

TEST(ComponentTest, CanChangeComponentEntityId) {
  Component1 comp1{};
  std::size_t entity_id = 3;
  comp1.SetEntityId(entity_id);
  ASSERT_EQ(comp1.GetEntityId(), entity_id);
}
