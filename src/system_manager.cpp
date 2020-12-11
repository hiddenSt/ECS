#include "system_manager.hpp"

void ecs::SystemManager::AddSystem(ecs::System* system) {
  // TODO: WayTooBad
  systems_topological_order_.push_back(system);
}

void ecs::SystemManager::PreUpdate() {
  for (auto system : systems_topological_order_) {
    system->PreUpdate();
  }
}

void ecs::SystemManager::Update() {
  for (auto system : systems_topological_order_) {
    system->Update();
  }
}

void ecs::SystemManager::PostUpdate() {
  for (auto system : systems_topological_order_) {
    system->PostUpdate();
  }
}

ecs::SystemManager& ecs::SystemManager::Instance() {
  if (instance_ == nullptr) {
    instance_ = new SystemManager();
  }

  return *instance_;
}
