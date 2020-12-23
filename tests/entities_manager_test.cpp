#include "entities_manager.hpp"

#include "gtest/gtest.h"
#include "utility/set_entities_id_container.hpp"

class EntitiesManagerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_ptr_ = new unsigned char[sizeof(ecs::EntitiesManager)];
    set_entities_id_container_ = new ecs::util::SetEntitiesIdContainer();
    ecs::EntitiesManager::Initialize(memory_ptr_, *set_entities_id_container_);
  }

  void TearDown() override {
    ecs::EntitiesManager::Destroy();
    delete[] memory_ptr_;
    delete set_entities_id_container_;
  }

  unsigned char* memory_ptr_;
  ecs::util::SetEntitiesIdContainer* set_entities_id_container_;
};

TEST_F(EntitiesManagerTest, CreatesUniqueId) {
  ecs::EntityId id_1 = ecs::EntitiesManager::Instance().CreateEntity();
  ecs::EntityId id_2 = ecs::EntitiesManager::Instance().CreateEntity();
  ASSERT_EQ(id_1, 1);
  ASSERT_EQ(id_2, 2);
}
