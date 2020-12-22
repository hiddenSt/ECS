#include "engine.hpp"

#include "gtest/gtest.h"

class EngineTest : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_arena_ = new unsigned char[500];
    ecs::Engine::Initialize(memory_arena_, 500, 10);
  }

  void TearDown() override {
    delete[] memory_arena_;
  }

  unsigned char* memory_arena_;

  struct Component1 : public ecs::ComponentType<Component1> {
    explicit Component1(int pa, int pb) : a(pa), b(pb) {
    }
    int a, b;
  };

  struct Component2 : public ecs::ComponentType<Component2> {
    explicit Component2(int pa, float pc) : a(pa), c(pc) {
    }
    int a;
    float c;
  };
};

TEST_F(EngineTest, CanAccessInstance) {
  ASSERT_NO_THROW(ecs::EntitiesManager::Instance());
}

TEST_F(EngineTest, CanAddComponent) {
  ecs::EntityId entity_id = ecs::Engine::Instance().CreateEntity();
  Component1* component_1 = ecs::Engine::Instance().AddComponent<Component1>(entity_id, 10 ,20);
  ASSERT_NE(component_1, nullptr);
}
