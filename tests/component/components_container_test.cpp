#include <gtest/gtest.h>

#include <tests/test_utility/test_component_type_1.hpp>

#include <allocators/pool_allocator/pool_allocator.hpp>
#include <ecs/component/component_type_container.hpp>
#include <ecs/utility/map_look_up_table.hpp>

class ComponentsContainerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    SetUpMemory();
    map_look_up_table_ = new ecs::util::MapLookUpTable();
    components_container_ =
        new ecs::component::ComponentTypeContainer<tests::utility::TestComponentType1,
                                                   allocators::PoolAllocator>(*pool_allocator_,
                                                                              *map_look_up_table_);
  }

  void TearDown() override {
    pool_allocator_->~PoolAllocator();
    delete[] allocated_memory_;
  }

  void SetUpMemory() {
    allocated_memory_ = new unsigned char[sizeof(tests::utility::TestComponentType1) * 2];
    pool_allocator_ = new allocators::PoolAllocator(allocated_memory_,
                                                    sizeof(tests::utility::TestComponentType1) * 2,
                                                    sizeof(tests::utility::TestComponentType1));
  }

  ecs::component::ComponentTypeContainer<tests::utility::TestComponentType1,
                                         allocators::PoolAllocator>* components_container_;
  unsigned char* allocated_memory_;
  allocators::PoolAllocator* pool_allocator_;
  ecs::util::MapLookUpTable* map_look_up_table_;
};

TEST_F(ComponentsContainerTest, ContainerHasCorrectComponentTypeId) {
  ASSERT_EQ(tests::utility::TestComponentType1::StaticGetComponentTypeId(),
            components_container_->GetComponentTypeId());
}

TEST_F(ComponentsContainerTest, AddComponent) {
  auto* pos = components_container_->AddComponent(1);
  auto* pos_comp = new (pos) tests::utility::TestComponentType1(10, 5, 23.5);
  ASSERT_EQ(pos_comp->field_1, 10);
  ASSERT_EQ(pos_comp->field_2, 5);
  ASSERT_EQ(pos_comp->field_3, 23.5);
}

TEST_F(ComponentsContainerTest, GetComponent) {
  auto* component = components_container_->AddComponent(1);
  auto* component_type_pointer = new (component) tests::utility::TestComponentType1(10, 5, 0.5);

  auto* component_request = components_container_->GetComponent(1);
  auto casted_to_component_type =
      static_cast<tests::utility::TestComponentType1*>(component_request);

  ASSERT_EQ(component, component_request);
  ASSERT_EQ(*component_type_pointer, *casted_to_component_type);
}

TEST_F(ComponentsContainerTest, RemoveComponent) {
  auto* component = components_container_->AddComponent(1);
  new (component) tests::utility::TestComponentType1();
  auto* component_request = components_container_->GetComponent(1);
  ASSERT_NE(component_request, nullptr);

  components_container_->RemoveComponent(1);
  component = components_container_->GetComponent(1);
  ASSERT_EQ(component, nullptr);
}

TEST_F(ComponentsContainerTest, ThrowsExceptionIfTryingToRemoveNotExistingComponent) {
  ASSERT_THROW(components_container_->RemoveComponent(1), std::logic_error);
}

TEST_F(ComponentsContainerTest, ThrowsExceptionIfTryingToAddComponentTypeThatEntityAlreadyHas) {
  auto* component = components_container_->AddComponent(1);
  new (component) tests::utility::TestComponentType1();
  ASSERT_THROW(components_container_->AddComponent(1), std::logic_error);
}

TEST_F(ComponentsContainerTest, MultipleAddWorks) {
  auto* component_1 = components_container_->AddComponent(1);
  auto* component_2 = components_container_->AddComponent(2);
  auto* comp_exmp_1 = new (component_1) tests::utility::TestComponentType1();
  auto* comp_exmp_2 = new (component_2) tests::utility::TestComponentType1();
  comp_exmp_1->SetEntityId(1);
  comp_exmp_2->SetEntityId(2);

  auto* component_of_entity2 =
      static_cast<tests::utility::TestComponentType1*>(components_container_->GetComponent(2));
  auto* component_of_entity1 =
      static_cast<tests::utility::TestComponentType1*>(components_container_->GetComponent(1));

  ASSERT_NE(component_of_entity1, nullptr);
  ASSERT_EQ(component_of_entity1->GetEntityId(), 1);

  ASSERT_NE(component_of_entity2, nullptr);
  ASSERT_EQ(component_of_entity2->GetEntityId(), 2);
}

TEST_F(ComponentsContainerTest, GetComponentTypeId) {
  ASSERT_EQ(components_container_->GetComponentTypeId(),
            tests::utility::TestComponentType1::StaticGetComponentTypeId());
}
