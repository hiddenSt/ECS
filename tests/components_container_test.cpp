#include "component_type.hpp"
#include "component_type_container.hpp"
#include "gtest/gtest.h"
#include "pool_allocator.hpp"

class ComponentsContainerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    auto* allocated_memory = new unsigned char[sizeof(ComponentExample) * 2];
    allocators::PoolAllocator pool_allocator{allocated_memory, sizeof(ComponentExample) * 2,
                                             sizeof(ComponentExample)};
    std::allocator<std::pair<const ecs::EntityId, ecs::Component*>> alloc;
    components_container_ = new ecs::ComponentTypeContainer<
        ComponentExample, allocators::PoolAllocator,
        std::allocator<std::pair<const ecs::EntityId, ecs::Component*>>>(pool_allocator, alloc);
  }

  struct ComponentExample : public ecs::ComponentType<ComponentExample> {
    int a;
    double c;
  };

  ecs::ComponentsContainer* components_container_;
};

TEST_F(ComponentsContainerTest, ContainerHasCorrectComponentTypeId) {
  ASSERT_EQ(ComponentExample::StaticGetComponentTypeId(),
            components_container_->GetComponentTypeId());
}

TEST_F(ComponentsContainerTest, AddComponent) {
  auto* pos = components_container_->AddComponent(1);
  auto pos_comp = static_cast<ComponentExample*>(pos);
  pos_comp->a = 10;
  pos_comp->c = 0.02;
  ASSERT_EQ(pos_comp->a, 10);
  ASSERT_EQ(pos_comp->c, 0.02);
}

TEST_F(ComponentsContainerTest, GetComponent) {
  auto* component = components_container_->AddComponent(1);
  auto component_type_pointer = static_cast<ComponentExample*>(component);
  component_type_pointer->a = 10;
  component_type_pointer->c = 0.02;
  auto* component_request = components_container_->GetComponent(1);
  auto casted_to_component_type = static_cast<ComponentExample*>(component_request);
  ASSERT_EQ(component, component_request);
  ASSERT_EQ(component_type_pointer, casted_to_component_type);
  ASSERT_EQ(component_type_pointer->a, casted_to_component_type->a);
  ASSERT_EQ(component_type_pointer->c, casted_to_component_type->c);
}

TEST_F(ComponentsContainerTest, RemoveComponent) {
  components_container_->AddComponent(1);
  auto* component = components_container_->GetComponent(1);
  ASSERT_NE(component, nullptr);

  components_container_->RemoveComponent(1);
  component = components_container_->GetComponent(1);
  ASSERT_EQ(component, nullptr);
}

TEST_F(ComponentsContainerTest, ThrowsExceptionIfTryingToRemoveNotExistingComponent) {
  ASSERT_THROW(components_container_->RemoveComponent(1), std::logic_error);
}

TEST_F(ComponentsContainerTest, ThrowsExceptionIfTryingToAddComponentTypeThatEntityAlreadyHas) {
  components_container_->AddComponent(1);
  ASSERT_THROW(components_container_->AddComponent(1), std::logic_error);
}

TEST_F(ComponentsContainerTest, MultipleAddWorks) {
  components_container_->AddComponent(1);
  components_container_->AddComponent(2);
  auto* component = static_cast<ComponentExample*>(components_container_->GetComponent(2));
  ASSERT_NE(component, nullptr);
}
