#include <ecs/manager/components_manager.hpp>

#include <string>

#include <gtest/gtest.h>

#include <ecs/component/component_type.hpp>
#include <allocators/pool_allocator/pool_allocator.hpp>
#include <ecs/utility/map_look_up_table.hpp>

class ComponentsManagerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    SetUpMemory();
    map_look_up_table1_ = new ecs::util::MapLookUpTable();
    map_look_up_table2_ = new ecs::util::MapLookUpTable();

    component_type1_container_ =
        new ecs::component::ComponentTypeContainer<ComponentType1, allocators::PoolAllocator>(
            *pool_allocator_1_, *map_look_up_table1_);
    component_type2_container_ =
        new ecs::component::ComponentTypeContainer<ComponentType2, allocators::PoolAllocator>(
            *pool_allocator_2_, *map_look_up_table2_);

    auto* memory = new unsigned char[sizeof(ecs::manager::ComponentsManager)];
    ecs::manager::ComponentsManager::Initialize(memory, ecs::component::Component::GetComponentsTypesCount());
    ecs::manager::ComponentsManager::Instance().AddComponentsContainer(component_type1_container_);
    ecs::manager::ComponentsManager::Instance().AddComponentsContainer(component_type2_container_);
  }

  void TearDown() override {
    ecs::manager::ComponentsManager::Destroy();
  }

  void SetUpMemory() {
    memory_arena_1_ = new unsigned char[sizeof(ComponentType1) * 2];
    memory_arena_2_ = new unsigned char[sizeof(ComponentType2) * 2];
    pool_allocator_1_ = new allocators::PoolAllocator(memory_arena_1_, sizeof(ComponentType1) * 2,
                                                      sizeof(ComponentType1));
    pool_allocator_2_ = new allocators::PoolAllocator(memory_arena_2_, sizeof(ComponentType2) * 2,
                                                      sizeof(ComponentType2));
  }

  struct ComponentType1 : public ecs::component::ComponentType<ComponentType1> {
    explicit ComponentType1(int pa, int pb, double pc) : a(pa), b(pb), c(pc) {
    }
    int a;
    int b;
    double c;
  };

  struct ComponentType2 : public ecs::component::ComponentType<ComponentType2> {
    explicit ComponentType2(int pa, const std::string& pstr) : a(pa), str(pstr) {
    }
    int a;
    std::string str;
  };

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
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType1>(1, 1, 2, 0.1);
  ASSERT_NE(component_type_1, nullptr);
  ASSERT_EQ(component_type_1->a, 1);
  ASSERT_EQ(component_type_1->b, 2);
  ASSERT_EQ(component_type_1->c, 0.1) << "C: " << component_type_1->c;

  auto* component_type_2 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(1, 15, "Hello world");
  ASSERT_NE(component_type_2, nullptr);
  ASSERT_EQ(component_type_2->a, 15);
  ASSERT_EQ(component_type_2->str, "Hello world");
}

TEST_F(ComponentsManagerTest, GetComponent) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType1>(1, 1, 2, 0.1);
  auto* component_type_2 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(1, 15, "Hello world");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  auto* component_type1_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType1>(1);
  auto* component_type2_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(1);

  ASSERT_EQ(component_type_1, component_type1_request);
  ASSERT_EQ(component_type_1->a, component_type1_request->a);
  ASSERT_EQ(component_type_1->b, component_type1_request->b);
  ASSERT_EQ(component_type_1->c, component_type1_request->c);

  ASSERT_EQ(component_type_2, component_type2_request);
  ASSERT_EQ(component_type_2->a, component_type2_request->a);
  ASSERT_EQ(component_type_2->str, component_type2_request->str);
}

TEST_F(ComponentsManagerTest, RemoveComponent) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType1>(1, 1, 2, 0.1);
  auto* component_type_2 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(1, 15, "Hello world");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  ecs::manager::ComponentsManager::Instance().RemoveComponent<ComponentType1>(1);
  auto* component_type1_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType1>(1);
  ASSERT_EQ(component_type1_request, nullptr);

  ecs::manager::ComponentsManager::Instance().RemoveComponent<ComponentType2>(1);
  auto* component_type2_request =
      ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(1);
  ASSERT_EQ(component_type2_request, nullptr);
}

TEST_F(ComponentsManagerTest, ComponentHasCorrectEntityId) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType1>(1, 1, 2, 0.1);
  auto* component_type_2 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(1, 15, "Hello world");

  ASSERT_EQ(component_type_1->GetEntityId(), 1);
  ASSERT_EQ(component_type_2->GetEntityId(), 1);
}

TEST_F(ComponentsManagerTest, GetComponentReturnsNullptrIfNoRequestedComponent) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType1>(1, 1, 2, 0.1);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType1>(2), nullptr);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(1), nullptr);
}

TEST_F(ComponentsManagerTest, WorksWithMultipleEntitys) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(1, 2, "EntityId1Comp");
  auto* component_type_2 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(4, 2, "EntityId4Comp");

  ASSERT_NE(component_type_1, nullptr);
  ASSERT_NE(component_type_2, nullptr);

  auto* entity1_request = ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(1);
  ASSERT_EQ(component_type_1, entity1_request);
  ASSERT_EQ(component_type_1->str, entity1_request->str);
  ASSERT_EQ(component_type_1->a, entity1_request->a);

  auto* entity2_request = ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(4);
  ASSERT_EQ(component_type_2, entity2_request);
  ASSERT_EQ(component_type_2->str, entity2_request->str);
  ASSERT_EQ(component_type_2->a, entity2_request->a);
}

TEST_F(ComponentsManagerTest, RemovesAllEntityComponents) {
  auto* component_type_1 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType1>(1, 2, 2, 0.2);
  auto* component_type_2 =
      ecs::manager::ComponentsManager::Instance().AddComponent<ComponentType2>(1, 2, "EntityId4Comp");
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType1>(1), component_type_1);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(1), component_type_2);

  ecs::manager::ComponentsManager::Instance().RemoveEntitiesComponents(1);

  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType1>(1), nullptr);
  ASSERT_EQ(ecs::manager::ComponentsManager::Instance().GetComponent<ComponentType2>(1), nullptr);
}

TEST_F(ComponentsManagerTest, CanGetIterator) {
  auto* iterator = ecs::manager::ComponentsManager::Instance().GetComponentsIterator<ComponentType1>();
  ASSERT_NE(iterator, nullptr);
}