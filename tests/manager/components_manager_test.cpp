#include <gtest/gtest.h>

#include <tests/test_utility/test_component_type_1.hpp>
#include <tests/test_utility/test_component_type_2.hpp>

#include <allocators/pool_allocator/pool_allocator.hpp>
#include <ecs/component/component_type.hpp>
#include <ecs/manager/components_manager.hpp>
#include <ecs/utility/map_look_up_table.hpp>
#include <string>

class ComponentsManagerTest : public ::testing::Test {
 protected:
  using TestComponent1 = tests::utility::TestComponentType1;
  using TestComponent2 = tests::utility::TestComponentType2;

  void SetUp() override {
    SetUpMemory();
    map_look_up_table1_ = new ecs::util::MapLookUpTable();
    map_look_up_table2_ = new ecs::util::MapLookUpTable();

    component_type1_container_ =
        new ecs::component::ComponentTypeContainer<TestComponent1, allocators::PoolAllocator>(
            *pool_allocator_1_, *map_look_up_table1_);
    component_type2_container_ =
        new ecs::component::ComponentTypeContainer<TestComponent2, allocators::PoolAllocator>(
            *pool_allocator_2_, *map_look_up_table2_);

    auto* memory = new unsigned char[sizeof(ecs::manager::ComponentsManager)];
    ecs::manager::ComponentsManager::Initialize(
        memory, ecs::component::Component::GetComponentsTypesCount());
    ecs::manager::ComponentsManager::Instance().AddComponentsContainer(component_type1_container_);
    ecs::manager::ComponentsManager::Instance().AddComponentsContainer(component_type2_container_);
  }

  void TearDown() override {
    ecs::manager::ComponentsManager::Destroy();
  }

  void SetUpMemory() {
    memory_arena_1_ = new unsigned char[sizeof(TestComponent1) * 2];
    memory_arena_2_ = new unsigned char[sizeof(TestComponent2) * 2];
    pool_allocator_1_ = new allocators::PoolAllocator(memory_arena_1_, sizeof(TestComponent1) * 2,
                                                      sizeof(TestComponent1));
    pool_allocator_2_ = new allocators::PoolAllocator(memory_arena_2_, sizeof(TestComponent2) * 2,
                                                      sizeof(TestComponent2));
  }

  unsigned char* memory_arena_1_;
  unsigned char* memory_arena_2_;
  ecs::util::MapLookUpTable* map_look_up_table1_;
  ecs::util::MapLookUpTable* map_look_up_table2_;
  allocators::PoolAllocator* pool_allocator_1_;
  allocators::PoolAllocator* pool_allocator_2_;
  ecs::component::ComponentsContainer* component_type1_container_;
  ecs::component::ComponentsContainer* component_type2_container_;
};

TEST_F(ComponentsManagerTest, AddComponent) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent1>(1, 1, 2, 0.1);
  ASSERT_NE(component_type_1, nullptr);
  ASSERT_EQ(component_type_1->field_1, 1);
  ASSERT_EQ(component_type_1->field_2, 2);
  ASSERT_EQ(component_type_1->field_3, 0.1);

  auto* component_type_2 = ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent2>(
      1, 15, 0.5, "Hello world");
  ASSERT_NE(component_type_2, nullptr);
  ASSERT_EQ(component_type_2->field_int, 15);
  ASSERT_EQ(component_type_2->field_double, 0.5);
  ASSERT_EQ(component_type_2->field_string, "Hello world");
}

TEST_F(ComponentsManagerTest, GetComponent) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent1>(1, 10, 10, 0.3);
  auto* component_type_2 = ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent2>(
      1, 15, 0.3, "Hello world");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  auto* component_type1_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent1>(1);
  auto* component_type2_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent2>(1);

  ASSERT_EQ(component_type_1, component_type1_request);
  ASSERT_EQ(*component_type_1, *component_type1_request);

  ASSERT_EQ(*component_type_2, *component_type2_request);
  ASSERT_EQ(component_type_2, component_type2_request);
}

TEST_F(ComponentsManagerTest, RemoveComponent) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent1>(1, 1, 2, 0.1);
  auto* component_type_2 = ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent2>(
      1, 15, 0.5, "Hello world");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  ecs::manager::ComponentsManager::Instance().RemoveComponent<TestComponent1>(1);
  auto* component_type1_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent1>(1);
  ASSERT_EQ(component_type1_request, nullptr);

  ecs::manager::ComponentsManager::Instance().RemoveComponent<TestComponent2>(1);
  auto* component_type2_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent2>(1);
  ASSERT_EQ(component_type2_request, nullptr);
}

TEST_F(ComponentsManagerTest, ComponentHasCorrectEntityId) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent1>(1, 1, 2, 0.1);
  auto* component_type_2 = ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent2>(
      1, 15, 0.5, "Hello world");

  ASSERT_EQ(component_type_1->GetEntityId(), 1);
  ASSERT_EQ(component_type_2->GetEntityId(), 1);
}

TEST_F(ComponentsManagerTest, MethodGetComponentReturnsNullptrIfNoRequestedComponent) {
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent1>(2), nullptr);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent2>(1), nullptr);
}

TEST_F(ComponentsManagerTest, WorksWithMultipleEntitys) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent1>(1, 2, 5, 0.5);
  auto* component_type_2 = ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent2>(
      4, 2, 0.7, "EntityId4Comp");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  auto* entity1_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent1>(1);
  ASSERT_EQ(component_type_1, entity1_request);
  ASSERT_EQ(*component_type_1, *entity1_request);

  auto* entity2_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent2>(4);
  ASSERT_EQ(component_type_2, entity2_request);
  ASSERT_EQ(*component_type_2, *entity2_request);
}

TEST_F(ComponentsManagerTest, RemovesAllEntityComponents) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent1>(1, 2, 2, 0.2);
  auto* component_type_2 = ecs::manager::ComponentsManager::Instance().AddComponent<TestComponent2>(
      1, 2, 0.5, "EntityId4Comp");
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent1>(1),
            component_type_1);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent2>(1),
            component_type_2);

  ecs::manager::ComponentsManager::Instance().RemoveEntitiesComponents(1);

  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent1>(1), nullptr);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<TestComponent2>(1), nullptr);
}

TEST_F(ComponentsManagerTest, CanGetIterator) {
  auto* iterator =
      ecs::manager::ComponentsManager::Instance().GetComponentsIterator<TestComponent1>();
  ASSERT_NE(iterator, nullptr);
}