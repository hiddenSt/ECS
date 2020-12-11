#include "components_manager.hpp"

#include <string>

#include "component_type.hpp"
#include "gtest/gtest.h"
#include "pool_allocator.hpp"

class ComponentManagerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_arena_1_ = new unsigned char[sizeof(ComponentType1) * 2];
    memory_arena_2_ = new unsigned char[sizeof(ComponentType2) * 2];
    pool_allocator_1_ = new allocators::PoolAllocator(memory_arena_1_, sizeof(ComponentType1) * 2,
                                                      sizeof(ComponentType1));
    pool_allocator_2_ = new allocators::PoolAllocator(memory_arena_2_, sizeof(ComponentType2) * 2,
                                                      sizeof(ComponentType2));
    map_alloc_1_ = new std::allocator<std::pair<const ecs::EntityId, ComponentType1*>>();
    map_alloc_2_ = new std::allocator<std::pair<const ecs::EntityId, ComponentType2*>>();
    component_type1_container_ = new ecs::ComponentTypeContainer<
        ComponentType1, allocators::PoolAllocator,
        std::allocator<std::pair<const ecs::EntityId, ComponentType1*>>>(*pool_allocator_1_,
                                                                         *map_alloc_1_);
    component_type2_container_ = new ecs::ComponentTypeContainer<
        ComponentType2, allocators::PoolAllocator,
        std::allocator<std::pair<const ecs::EntityId, ComponentType2*>>>(*pool_allocator_2_,
                                                                         *map_alloc_2_);

    components_manager_ = new ecs::ComponentsManager(ecs::Component::GetComponentsTypesCount());
    components_manager_->AddComponentContainer(component_type1_container_);
    components_manager_->AddComponentContainer(component_type2_container_);
  }

  void TearDown() override {
  }

  struct ComponentType1 : public ecs::ComponentType<ComponentType1> {
    explicit ComponentType1(int pa, int pb, double pc) : a(pa), b(pb), c(pc) {
    }
    int a;
    int b;
    double c;
  };

  struct ComponentType2 : public ecs::ComponentType<ComponentType2> {
    explicit ComponentType2(int pa, const std::string& pstr) : a(pa), str(pstr) {
    }
    int a;
    std::string str;
  };

  unsigned char* memory_arena_1_;
  unsigned char* memory_arena_2_;
  allocators::PoolAllocator* pool_allocator_1_;
  allocators::PoolAllocator* pool_allocator_2_;
  std::allocator<std::pair<const ecs::EntityId, ComponentType1*>>* map_alloc_1_;
  std::allocator<std::pair<const ecs::EntityId, ComponentType2*>>* map_alloc_2_;
  ecs::ComponentsContainer* component_type1_container_;
  ecs::ComponentsContainer* component_type2_container_;
  ecs::ComponentsManager* components_manager_;
};

TEST_F(ComponentManagerTest, AddComponent) {
  auto* component_type_1 = components_manager_->AddComponent<ComponentType1>(1, 1, 2, 0.1);
  ASSERT_NE(component_type_1, nullptr);
  ASSERT_EQ(component_type_1->a, 1);
  ASSERT_EQ(component_type_1->b, 2);
  ASSERT_EQ(component_type_1->c, 0.1) << "C: " << component_type_1->c;

  ComponentType2* component_type_2 =
      components_manager_->AddComponent<ComponentType2>(1, 15, "Hello world");
  ASSERT_NE(component_type_2, nullptr);
  ASSERT_EQ(component_type_2->a, 15);
  ASSERT_EQ(component_type_2->str, "Hello world");
}

TEST_F(ComponentManagerTest, GetComponent) {
  auto* component_type_1 = components_manager_->AddComponent<ComponentType1>(1, 1, 2, 0.1);
  auto* component_type_2 = components_manager_->AddComponent<ComponentType2>(1, 15, "Hello world");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  auto* component_type1_request = components_manager_->GetComponent<ComponentType1>(1);
  auto* component_type2_request = components_manager_->GetComponent<ComponentType2>(1);

  ASSERT_EQ(component_type_1, component_type1_request);
  ASSERT_EQ(component_type_2, component_type2_request);

  ASSERT_EQ(component_type_1->a, component_type1_request->a);
  ASSERT_EQ(component_type_1->b, component_type1_request->b);
  ASSERT_EQ(component_type_1->c, component_type1_request->c);
  ASSERT_EQ(component_type_2->a, component_type2_request->a);
  ASSERT_EQ(component_type_2->str, component_type2_request->str);
}

TEST_F(ComponentManagerTest, RemoveComponent) {
  auto* component_type_1 = components_manager_->AddComponent<ComponentType1>(1, 1, 2, 0.1);
  auto* component_type_2 = components_manager_->AddComponent<ComponentType2>(1, 15, "Hello world");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  components_manager_->RemoveComponent<ComponentType1>(1);
  auto* component_type1_request = components_manager_->GetComponent<ComponentType1>(1);
  ASSERT_EQ(component_type1_request, nullptr);

  components_manager_->RemoveComponent<ComponentType2>(1);
  auto* component_type2_request = components_manager_->GetComponent<ComponentType2>(1);
  ASSERT_EQ(component_type2_request, nullptr);
}

TEST_F(ComponentManagerTest, ComponentHasCorrectEntityId) {
  auto* component_type_1 = components_manager_->AddComponent<ComponentType1>(1, 1, 2, 0.1);
  auto* component_type_2 = components_manager_->AddComponent<ComponentType2>(1, 15, "Hello world");

  ASSERT_EQ(component_type_1->GetEntityId(), 1);
  ASSERT_EQ(component_type_2->GetEntityId(), 1);
}

TEST_F(ComponentManagerTest, GetComponentReturnsNullptrIfNoRequestedComponent) {
  auto* component_type_1 = components_manager_->AddComponent<ComponentType1>(1, 1, 2, 0.1);
  ASSERT_EQ(components_manager_->GetComponent<ComponentType1>(2), nullptr);
  ASSERT_EQ(components_manager_->GetComponent<ComponentType2>(1), nullptr);
}