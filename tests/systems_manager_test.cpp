#include "system_type.hpp"
#include "systems_manager.hpp"

#include "gtest/gtest.h"

class SystemsManagerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ecs::SystemsManager::Initialize();
  }

  void TearDown() override {

  }

  struct System1 : public ecs::SystemType<System1> {
    System1(std::vector<std::size_t>& vec) : order_1(vec) {}
    void Update() override {
      order_1.push_back(1);
    }
    std::vector<std::size_t>& order_1;
  };

  struct System2 : public ecs::SystemType<System2> {
    System2(std::vector<std::size_t>& vec) : order_2(vec) {}
    void Update() override {
      order_2.push_back(2);
    }
    std::vector<std::size_t>& order_2;
  };

  struct System3 : public ecs::SystemType<System3> {
    System3(std::vector<std::size_t>& vec) : order_3(vec) {}
    void Update() override {
      order_3.push_back(2);
    }
    std::vector<std::size_t>& order_3;
  };


  std::vector<std::size_t> order;

};

TEST_F(SystemsManagerTest, AddSystem) {
}

TEST_F(SystemsManagerTest, AddDependency) {
}

TEST_F(SystemsManagerTest, FindsTopoligicalOrder) {
  System1 *system_1 = new System1(order);
  System2 *system_2 = new System2(order);
  System3 *system_3 = new System3(order);
  ecs::SystemsManager::Instance().AddSystem(system_1);
  ecs::SystemsManager::Instance().AddSystem(system_2);
  ecs::SystemsManager::Instance().AddSystem(system_3);
  ecs::SystemsManager::Instance().AddDependency(system_1, system_2);
  ecs::SystemsManager::Instance().AddDependency(system_2, system_3);

  ASSERT_EQ(order[0], 3);
  ASSERT_EQ(order[1], 2);
  ASSERT_EQ(order[2], 1);
}

TEST_F(SystemsManagerTest, CallingSystemsMethodsInTopologicalOrder) {
}

TEST_F(SystemsManagerTest, ThrowsExceptionIfSystemsDependencyHasCycle) {
}
