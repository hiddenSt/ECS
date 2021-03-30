#include <gtest/gtest.h>

#include <tests/test_utility/test_component_type_1.hpp>
#include <tests/test_utility/test_component_type_2.hpp>

#include <ecs/engine.hpp>

class EngineTest : public ::testing::Test {
 protected:
  using TestComponent1 = tests::utility::TestComponentType1;
  using TestComponent2 = tests::utility::TestComponentType2;

  void SetUp() override {
    memory_arena_ = new unsigned char[500];
    ecs::Engine::Initialize(memory_arena_, 500, 10);
  }

  void TearDown() override {
    ecs::Engine::Instance().ShutDown();
    delete[] memory_arena_;
  }

  unsigned char* memory_arena_;


  class System1 : public ecs::system::SystemType<System1> {
   private:
    int a;
  };
};

TEST_F(EngineTest, CanAccessInstance) {
  ASSERT_NO_THROW(ecs::Engine::Instance());
}

TEST_F(EngineTest, CanCreateEntity) {
  ASSERT_NO_THROW(ecs::Engine::Instance().CreateEntity());
}

TEST_F(EngineTest, CanAddComponent) {
  ecs::EntityId entity_id = ecs::Engine::Instance().CreateEntity();
  auto* component_1 = ecs::Engine::Instance().AddComponent<TestComponent1>(entity_id, 10, 20, 0.5);
  ASSERT_NE(component_1, nullptr);
}

TEST_F(EngineTest, CanGetComponenet) {
  ecs::EntityId entity_id = ecs::Engine::Instance().CreateEntity();
  auto* component_1 = ecs::Engine::Instance().AddComponent<TestComponent1>(entity_id, 10, 20, 0.5);
  auto* request = ecs::Engine::Instance().GetComponent<TestComponent1>(entity_id);
  ASSERT_EQ(component_1, request);
  ASSERT_EQ(*component_1, *request);
}

TEST_F(EngineTest, RemovesComponentsFromEntity) {
  ecs::EntityId entity_id = ecs::Engine::Instance().CreateEntity();
  auto* component_1 = ecs::Engine::Instance().AddComponent<TestComponent1>(entity_id, 10, 20, 0.5);
  ASSERT_NE(component_1, nullptr);
  ecs::Engine::Instance().RemoveComponent<TestComponent1>(entity_id);
  auto* request = ecs::Engine::Instance().GetComponent<TestComponent1>(entity_id);
  ASSERT_EQ(request, nullptr);
}

TEST_F(EngineTest, CanAddSystem) {
  ecs::system::System* system = nullptr;
  ASSERT_NO_THROW(system = ecs::Engine::Instance().AddSystem<System1>());
  ASSERT_NE(system, nullptr);
}
