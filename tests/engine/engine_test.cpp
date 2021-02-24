#include <ecs/engine.hpp>

#include <gtest/gtest.h>

class EngineTest : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_arena_ = new unsigned char[500];
    ecs::Engine::Initialize(memory_arena_, 500, 10);
  }

  void TearDown() override {
    ecs::Engine::Instance().ShutDown();
    delete[] memory_arena_;
  }

  unsigned char* memory_arena_;

  struct Component1 : public ecs::component::ComponentType<Component1> {
    explicit Component1(int pa, int pb) : a(pa), b(pb) {
    }
    int a, b;
  };

  struct Component2 : public ecs::component::ComponentType<Component2> {
    explicit Component2(int pa, float pc) : a(pa), c(pc) {
    }
    int a;
    float c;
  };

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
  Component1* component_1 = ecs::Engine::Instance().AddComponent<Component1>(entity_id, 10, 20);
  ASSERT_NE(component_1, nullptr);
}

TEST_F(EngineTest, CanGetComponenet) {
  ecs::EntityId entity_id = ecs::Engine::Instance().CreateEntity();
  Component1* component_1 = ecs::Engine::Instance().AddComponent<Component1>(entity_id, 10, 20);
  Component1* request = ecs::Engine::Instance().GetComponent<Component1>(entity_id);
  ASSERT_EQ(component_1, request);
  ASSERT_EQ(component_1->a, request->a);
  ASSERT_EQ(component_1->b, request->b);
}

TEST_F(EngineTest, RemovesComponentsFromEntity) {
  ecs::EntityId entity_id = ecs::Engine::Instance().CreateEntity();
  Component1* component_1 = ecs::Engine::Instance().AddComponent<Component1>(entity_id, 10, 20);
  ASSERT_NE(component_1, nullptr);
  ecs::Engine::Instance().RemoveComponent<Component1>(entity_id);
  Component1* request = ecs::Engine::Instance().GetComponent<Component1>(entity_id);
  ASSERT_EQ(request, nullptr);
}

TEST_F(EngineTest, CanAddSystem) {
  ecs::system::System* system = nullptr;
  ASSERT_NO_THROW(system = ecs::Engine::Instance().AddSystem<System1>());
  ASSERT_NE(system, nullptr);
}
