#include "gtest/gtest.h"

#include <memory>

#include "component_type.hpp"
#include "component_type_container.hpp"
#include "pool_allocator.hpp"

class ComponentsContainerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    unsigned char* allocated_memory = new unsigned char[sizeof(Position)*2];
    allocators::PoolAllocator pool_allocator{allocated_memory, sizeof(Position)*2, sizeof(Position)};
    std::allocator<std::pair<const ecs::EntityId, ecs::Component*>> alloc;
    components_container_ = new ecs::ComponentTypeContainer<Position, allocators::PoolAllocator, std::allocator<std::pair<const ecs::EntityId, ecs::Component*>>>(pool_allocator, alloc);
  }

  void TearDown() override {

  }

  struct Position : public ecs::ComponentType<Position> {
    int a;
    double c;
  };

  ecs::ComponentsContainer* components_container_;
};

TEST_F(ComponentsContainerTest, AddComponent) {
  auto* pos = components_container_->AddComponent(1);
  auto pos_comp = static_cast<Position*>(pos);
  pos_comp->a = 10;
  pos_comp->c = 0.02;
  ASSERT_EQ(pos_comp->a, 10);
  ASSERT_EQ(pos_comp->c, 0.02);
}

TEST_F(ComponentsContainerTest, GetComponent) {
  auto* pos = components_container_->AddComponent(1);
  auto pos_comp = static_cast<Position*>(pos);
  pos_comp->a = 10;
  pos_comp->c = 0.02;
  auto* pos_request = components_container_->GetComponent(1);
  auto pos_comp_request = static_cast<Position*>(pos_request);
  ASSERT_EQ(pos, pos_request);
  ASSERT_EQ(pos_comp, pos_comp_request);
  ASSERT_EQ(pos_comp->a, pos_comp_request->a);
  ASSERT_EQ(pos_comp->c, pos_comp_request->c);
}

TEST_F(ComponentsContainerTest, RemoveComponent) {

}