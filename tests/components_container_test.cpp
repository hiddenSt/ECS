#include "component_type.hpp"
#include "component_type_container.hpp"
#include "gtest/gtest.h"
#include "pool_allocator.hpp"

class ComponentsContainerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    allocated_memory_ = new unsigned char[sizeof(ComponentExample) * 2];
    pool_allocator_ = new allocators::PoolAllocator(allocated_memory_, sizeof(ComponentExample) * 2,
                                                         sizeof(ComponentExample));
    alloc_ = new std::allocator<std::pair<const ecs::EntityId, ComponentExample*>>;
    components_container_ = new ecs::ComponentTypeContainer<
        ComponentExample, allocators::PoolAllocator,
        std::allocator<std::pair<const ecs::EntityId, ComponentExample*>>>(*pool_allocator_, *alloc_);
  }

  void TearDown() override {
    delete alloc_;
    delete pool_allocator_;
    delete allocated_memory_;
  }

  struct ComponentExample : public ecs::ComponentType<ComponentExample> {
    ComponentExample(int a1, double c1) : a(a1), c(c1), d(0.9) {}
    int a;
    double c;
    double d;
  };

  ecs::ComponentTypeContainer<
      ComponentExample, allocators::PoolAllocator,
      std::allocator<std::pair<const ecs::EntityId, ComponentExample*>>> *components_container_;

  unsigned char* allocated_memory_;
  std::allocator<std::pair<const ecs::EntityId, ComponentExample*>>* alloc_;
  allocators::PoolAllocator* pool_allocator_;
};

TEST_F(ComponentsContainerTest, ContainerHasCorrectComponentTypeId) {
  ASSERT_EQ(ComponentExample::StaticGetComponentTypeId(),
            components_container_->GetComponentTypeId());
}

TEST_F(ComponentsContainerTest, AddComponent) {
  auto* pos = components_container_->AddComponent(1, 10, 0.02);
  auto pos_comp = static_cast<ComponentExample*>(pos);
  ASSERT_EQ(pos_comp->a, 10);
  ASSERT_EQ(pos_comp->c, 0.02);
}

TEST_F(ComponentsContainerTest, GetComponent) {
  auto* component = components_container_->AddComponent(1, 10, 0.02);
  auto component_type_pointer = static_cast<ComponentExample*>(component);

  auto* component_request = components_container_->GetComponent(1);
  auto casted_to_component_type = static_cast<ComponentExample*>(component_request);

  ASSERT_EQ(component, component_request);
  ASSERT_EQ(component_type_pointer, casted_to_component_type);

  ASSERT_EQ(component_type_pointer->a, casted_to_component_type->a);
  ASSERT_EQ(component_type_pointer->c, casted_to_component_type->c);
}

TEST_F(ComponentsContainerTest, RemoveComponent) {
  components_container_->AddComponent(1, 0, 0);
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
  components_container_->AddComponent(1, 0, 0);
  ASSERT_THROW(components_container_->AddComponent(1, 0, 0), std::logic_error);
}

TEST_F(ComponentsContainerTest, MultipleAddWorks) {
  components_container_->AddComponent(1, 0, 0);
  components_container_->AddComponent(2, 0, 0);
  auto* component_of_entity2 = static_cast<ComponentExample*>(components_container_->GetComponent(2));
  auto* component_of_entity1 = static_cast<ComponentExample*>(components_container_->GetComponent(1));

  ASSERT_NE(component_of_entity1, nullptr);
  ASSERT_EQ(component_of_entity1->GetEntityId(), 1);

  ASSERT_NE(component_of_entity2, nullptr);
  ASSERT_EQ(component_of_entity2->GetEntityId(), 2);
}
