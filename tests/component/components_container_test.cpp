#include <ecs/component/component_type.hpp>
#include <ecs/component/component_type_container.hpp>
#include <gtest/gtest.h>
#include <allocators/pool_allocator/pool_allocator.hpp>
#include <ecs/utility/map_look_up_table.hpp>

class ComponentsContainerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    SetUpMemory();
    map_look_up_table_ = new ecs::util::MapLookUpTable();
    components_container_ =
        new ecs::component::ComponentTypeContainer<ComponentExample, allocators::PoolAllocator>(
            *pool_allocator_, *map_look_up_table_);
  }

  void TearDown() override {
  }

  void SetUpMemory() {
    allocated_memory_ = new unsigned char[sizeof(ComponentExample) * 2];
    pool_allocator_ = new allocators::PoolAllocator(allocated_memory_, sizeof(ComponentExample) * 2,
                                                    sizeof(ComponentExample));
  }

  struct ComponentExample : public ecs::component::ComponentType<ComponentExample> {
    ComponentExample(int a1, double c1) : a(a1), c(c1), d(0.9) {
    }
    int a;
    double c;
    double d;
  };

  ecs::component::ComponentTypeContainer<ComponentExample, allocators::PoolAllocator>* components_container_;
  unsigned char* allocated_memory_;
  allocators::PoolAllocator* pool_allocator_;
  ecs::util::MapLookUpTable* map_look_up_table_;
};

TEST_F(ComponentsContainerTest, ContainerHasCorrectComponentTypeId) {
  ASSERT_EQ(ComponentExample::StaticGetComponentTypeId(),
            components_container_->GetComponentTypeId());
}

TEST_F(ComponentsContainerTest, AddComponent) {
  auto* pos = components_container_->AddComponent(1);
  auto* pos_comp = new (pos) ComponentExample(10, 0.02);
  pos_comp->a = 10;
  pos_comp->c = 0.02;
  ASSERT_EQ(pos_comp->a, 10);
  ASSERT_EQ(pos_comp->c, 0.02);
}

TEST_F(ComponentsContainerTest, GetComponent) {
  auto* component = components_container_->AddComponent(1);
  auto* component_type_pointer = new (component) ComponentExample(10, 0.01);

  auto* component_request = components_container_->GetComponent(1);
  auto casted_to_component_type = static_cast<ComponentExample*>(component_request);

  ASSERT_EQ(component, component_request);
  ASSERT_EQ(component_type_pointer, casted_to_component_type);

  ASSERT_EQ(component_type_pointer->a, casted_to_component_type->a);
  ASSERT_EQ(component_type_pointer->c, casted_to_component_type->c);
}

TEST_F(ComponentsContainerTest, RemoveComponent) {
  auto* component = components_container_->AddComponent(1);
  new (component) ComponentExample(10, 0.02);
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
  new (component) ComponentExample(10, 0.02);
  ASSERT_THROW(components_container_->AddComponent(1), std::logic_error);
}

TEST_F(ComponentsContainerTest, MultipleAddWorks) {
  auto* component_1 = components_container_->AddComponent(1);
  auto* component_2 = components_container_->AddComponent(2);
  auto* comp_exmp_1 = new (component_1) ComponentExample(1, 9.8);
  auto* comp_exmp_2 = new (component_2) ComponentExample(-91, 0.1);
  comp_exmp_1->SetEntityId(1);
  comp_exmp_2->SetEntityId(2);

  auto* component_of_entity2 =
      static_cast<ComponentExample*>(components_container_->GetComponent(2));
  auto* component_of_entity1 =
      static_cast<ComponentExample*>(components_container_->GetComponent(1));

  ASSERT_NE(component_of_entity1, nullptr);
  ASSERT_EQ(component_of_entity1->GetEntityId(), 1);

  ASSERT_NE(component_of_entity2, nullptr);
  ASSERT_EQ(component_of_entity2->GetEntityId(), 2);
}

TEST_F(ComponentsContainerTest, GetComponentTypeId) {
  ASSERT_EQ(components_container_->GetComponentTypeId(),
            ComponentExample::StaticGetComponentTypeId());
}
