#include "system_manager.hpp"

void ecs::SystemManager::AddSystem(ecs::System *system) {

}

void ecs::SystemManager::PreUpdate() {
  for (auto system: systems_topological_order_) {
    system->PreUpdate();
  }
}

void ecs::SystemManager::Update() {
  for (auto system: systems_topological_order_) {
    system->Update();
  }
}

void ecs::SystemManager::PostUpdate() {
  for (auto system: systems_topological_order_) {
    system->PostUpdate();
  }
}
