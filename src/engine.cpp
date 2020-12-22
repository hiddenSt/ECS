#include "engine.hpp"
#include "component.hpp"
#include "stack_allocator.hpp"

#include <stdexcept>

ecs::Engine* ecs::Engine::instance_ = nullptr;

ecs::Engine& ecs::Engine::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error("Engine is not initialized.");
  }

  return *instance_;
}

void ecs::Engine::Initialize(std::size_t max_components_per_types) {
  for (std::size_t i = 0; i < Component::GetComponentsTypesCount(); ++i) {
  }
}

ecs::Engine::Engine() : memory_size_bytes_(0) {}

ecs::EntityId ecs::Engine::CreateEntity() {
  return EntitiesManager::Instance().CreateEntity();
}

void ecs::Engine::MakeTic() {
  SystemsManager::Instance().PreUpdate();
  SystemsManager::Instance().Update();
  SystemsManager::Instance().PostUpdate();
}

void ecs::Engine::SetUp() {
  SystemsManager::Instance().SetUp();
}

void ecs::Engine::ShutDown() {
}

