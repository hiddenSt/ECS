#include <gtest/gtest.h>

#include <ecs/component/component_type.hpp>

TEST(ComponentTest, ComponentTypeGetsId) {
  class Component1 : public ecs::component::ComponentType<Component1> {
    int a;
    float b;
  };
  ASSERT_EQ(Component1::StaticGetComponentTypeId(), 1);
}

TEST(ComponentTest, ComponentTypeInstanceReturnsCorrectId) {
  class Component1 : public ecs::component::ComponentType<Component1> {
    int a;
    float b;
  };
  Component1 comp1{};

  ASSERT_EQ(Component1::StaticGetComponentTypeId(), comp1.GetComponentTypeId());
}

TEST(ComponentTest, GeneratesCorrectUniqueIdForEveryComponentType) {
  class Component1 : public ecs::component::ComponentType<Component1> {
    int a;
    float b;
  };

  class Component2 : public ecs::component::ComponentType<Component2> {
    int a;
    float b;
  };

  std::size_t comp_1_id = Component1::StaticGetComponentTypeId();
  ASSERT_EQ(comp_1_id, Component1::StaticGetComponentTypeId());

  std::size_t comp_2_id = Component2::StaticGetComponentTypeId();
  ASSERT_EQ(comp_2_id, Component2::StaticGetComponentTypeId());

  ASSERT_EQ(comp_2_id - comp_1_id, 1) << "Comp1: " << comp_1_id << " Comp2: " << comp_2_id;
}

TEST(ComponentTest, ComponentHasDefaultEntityIdEqualsTo0) {
  class Component1 : public ecs::component::ComponentType<Component1> {
    int a, b;
  };

  Component1 comp1{};
  ASSERT_EQ(comp1.GetEntityId(), 0);
}

TEST(ComponentTest, CanChangeComponentEntityId) {
  class Component1 : public ecs::component::ComponentType<Component1> {
    float a, b;
  };

  Component1 comp1{};
  comp1.SetEntityId(2);
  ASSERT_EQ(comp1.GetEntityId(), 2);
}
