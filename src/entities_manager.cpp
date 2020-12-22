#include "entities_manager.hpp"

ecs::EntitiesManager* ecs::EntitiesManager::instance_ = nullptr;

ecs::EntitiesManager& ecs::EntitiesManager::Instance() {
  return *instance_;
}

ecs::EntitiesManager& ecs::EntitiesManager::Create(ecs::EntitiesIdContainer& entities_id_container) {
  if (instance_ == nullptr) {
    instance_ = new EntitiesManager(entities_id_container);
  }

  return *instance_;
}

ecs::EntitiesManager::EntitiesManager(ecs::EntitiesIdContainer& entities_id_container)
    : entities_id_container_(entities_id_container), entities_counter_(0) {}

ecs::EntityId ecs::EntitiesManager::CreateEntity() {
  EntityId new_id = ++entities_counter_;
  entities_id_container_.Insert(new_id);
  return new_id;
}

void ecs::EntitiesManager::RemoveEntity(const ecs::EntityId& entity_id) {
  entities_id_container_.Remove(entity_id);
}