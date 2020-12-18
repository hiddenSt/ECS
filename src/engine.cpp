#include "engine.hpp"

#include <stdexcept>

ecs::Engine* ecs::Engine::instance_ = nullptr;

ecs::Engine& ecs::Engine::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error("Engine is not initialized.");
  }

  return *instance_;
}

void ecs::Engine::Initialize() {
}

ecs::EntityId ecs::Engine::CreateEntity() {
  return entity_manager_.CreateEntity();
}

void ecs::Engine::MakeTic() {
  system_manager_.PreUpdate();
  system_manager_.Update();
  system_manager_.PostUpdate();
}

void ecs::Engine::SetUp() {
  system_manager_.SetUp();
}

void ecs::Engine::ShutDown() {
}

