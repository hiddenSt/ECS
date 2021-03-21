#include <gtest/gtest.h>

#include <ecs/component/component_type.hpp>
#include <ecs/iterator/component_type_iterator.hpp>
#include <ecs/utility/map_components_iterator.hpp>
#include <ecs/utility/map_look_up_table.hpp>

class ComponentsIteratorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    map_look_up_table_ = new ecs::util::MapLookUpTable();
    for (std::size_t i = 0; i < 10; ++i) {
      ecs::component::Component* component = new ComponentT1(10, 9.0);
      component->SetEntityId(i);
      map_look_up_table_->Insert(i, component);
    }
    iterator_ = map_look_up_table_->GetIterator();
    type_iterator_ = new ecs::iterator::ComponentTypeIterator<ComponentT1>(iterator_);
  }

  struct ComponentT1 : public ecs::component::ComponentType<ComponentT1> {
    explicit ComponentT1(int pa, float pb) : a(pa), b(pb) {
    }
    int a;
    int b;
  };

  ecs::iterator::ComponentsIterator* iterator_;
  ecs::iterator::ComponentTypeIterator<ComponentT1>* type_iterator_;
  ecs::util::MapLookUpTable* map_look_up_table_;
};

TEST_F(ComponentsIteratorTest, IteratorWorks) {
  int i = 0;
  std::vector<ecs::EntityId> entity_ids;
  for (type_iterator_->First(); !type_iterator_->IsDone(); type_iterator_->Next()) {
    entity_ids.push_back(type_iterator_->GetCurrentComponent()->GetEntityId());
    ++i;
  }

  ASSERT_EQ(i, 10);

  std::sort(entity_ids.begin(), entity_ids.end());

  for (std::size_t j = 0; j < 10; ++j) {
    ASSERT_EQ(j, entity_ids[j]);
  }
}
