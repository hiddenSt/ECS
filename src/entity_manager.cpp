#include "entity_manager.hpp"

ecs::EntityManager& ecs::EntityManager::Instance() {
  if (instance_ == nullptr) {
    instance_ = new EntityManager();
  }

  return *instance_;
}
