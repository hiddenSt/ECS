#include "entity_manager.hpp"

ecs::EntityManager& ecs::EntityManager::Instance() {
  return *instance_;
}

ecs::EntityManager& ecs::EntityManager::Create(ecs::EntitysIdContainer& entitys_id_container) {
  if (instance_ == nullptr) {
    instance_ = new EntityManager(entitys_id_container);
  }

  return *instance_;
}

ecs::EntityManager::EntityManager(ecs::EntitysIdContainer& entitys_id_container)
    : entitys_id_container_(entitys_id_container) {
  entitys_counter_ = 0;
}

ecs::EntityId ecs::EntityManager::CreateEntity() {
  EntityId new_id = ++entitys_counter_;
  entitys_id_container_.Insert(new_id);
  return new_id;
}

void ecs::EntityManager::RemoveEntity(const ecs::EntityId& entity_id) {
  entitys_id_container_.Remove(entity_id);
}