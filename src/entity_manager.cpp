#include "entity_manager.hpp"

ecs::EntityManager* ecs::EntityManager::instance_ = nullptr;

ecs::EntityManager& ecs::EntityManager::Instance() {
  return *instance_;
}

ecs::EntityManager& ecs::EntityManager::Create(ecs::EntitiesIdContainer& entities_id_container) {
  if (instance_ == nullptr) {
    instance_ = new EntityManager(entities_id_container);
  }

  return *instance_;
}

ecs::EntityManager::EntityManager(ecs::EntitiesIdContainer& entities_id_container)
    : entities_id_container_(entities_id_container), entities_counter_(0) {}

ecs::EntityId ecs::EntityManager::CreateEntity() {
  EntityId new_id = ++entities_counter_;
  entities_id_container_.Insert(new_id);
  return new_id;
}

void ecs::EntityManager::RemoveEntity(const ecs::EntityId& entity_id) {
  entities_id_container_.Remove(entity_id);
}