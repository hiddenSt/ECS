#include <ecs/manager/systems_manager.hpp>

#include <gtest/gtest.h>
#include <ecs/system/system_type.hpp>

class SystemsManagerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_ptr_ = new unsigned char[sizeof(ecs::manager::SystemsManager)];
    ecs::manager::SystemsManager::Initialize(memory_ptr_);
  }

  void TearDown() override {
    ecs::manager::SystemsManager::Destroy();
    delete[] memory_ptr_;
  }

  struct System1 : public ecs::system::SystemType<System1> {
    System1(std::vector<std::size_t>& vec) : order_1(vec) {
    }
    void Update() override {
      order_1.push_back(1);
    }
    std::vector<std::size_t>& order_1;
  };

  struct System2 : public ecs::system::SystemType<System2> {
    System2(std::vector<std::size_t>& vec) : order_2(vec) {
    }
    void Update() override {
      order_2.push_back(2);
    }
    std::vector<std::size_t>& order_2;
  };

  struct System3 : public ecs::system::SystemType<System3> {
    System3(std::vector<std::size_t>& vec) : order_3(vec) {
    }
    void Update() override {
      order_3.push_back(3);
    }
    std::vector<std::size_t>& order_3;
  };

  unsigned char* memory_ptr_;
  std::vector<std::size_t> order;
};

TEST_F(SystemsManagerTest, SystemsInokesInTopologicalOrder) {
  auto* system_1 = new System1(order);
  auto* system_2 = new System2(order);
  auto* system_3 = new System3(order);

  ecs::manager::SystemsManager::Instance().AddSystem(system_1);
  ecs::manager::SystemsManager::Instance().AddSystem(system_2);
  ecs::manager::SystemsManager::Instance().AddSystem(system_3);
  ecs::manager::SystemsManager::Instance().AddDependency(system_1, system_2);
  ecs::manager::SystemsManager::Instance().AddDependency(system_2, system_3);
  ecs::manager::SystemsManager::Instance().SetUp();
  ecs::manager::SystemsManager::Instance().Update();

  ASSERT_EQ(order[0], 3);
  ASSERT_EQ(order[1], 2);
  ASSERT_EQ(order[2], 1);
}

TEST_F(SystemsManagerTest, ThrowsExceptionIfSystemSelfDependent) {
  auto* system_1 = new System1(order);
  ecs::manager::SystemsManager::Instance().AddSystem(system_1);
  ecs::manager::SystemsManager::Instance().AddDependency(system_1, system_1);
  ASSERT_THROW(ecs::manager::SystemsManager::Instance().SetUp(), std::logic_error);
}

TEST_F(SystemsManagerTest, ThrowsExceptionIfSystemsDependencyHasCycle) {
  auto* system_1 = new System1(order);
  auto* system_2 = new System2(order);
  auto* system_3 = new System3(order);

  ecs::manager::SystemsManager::Instance().AddSystem(system_1);
  ecs::manager::SystemsManager::Instance().AddSystem(system_2);
  ecs::manager::SystemsManager::Instance().AddSystem(system_3);
  ecs::manager::SystemsManager::Instance().AddDependency(system_1, system_2);
  ecs::manager::SystemsManager::Instance().AddDependency(system_2, system_3);
  ecs::manager::SystemsManager::Instance().AddDependency(system_3, system_1);

  ASSERT_THROW(ecs::manager::SystemsManager::Instance().SetUp(), std::logic_error);
}
