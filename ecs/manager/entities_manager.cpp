#include <ecs/manager/entities_manager.hpp>

#include <memory>

namespace ecs {
namespace manager {

EntitiesManager* EntitiesManager::instance_ = nullptr;

EntitiesManager& EntitiesManager::Instance() {
  return *instance_;
}

EntitiesManager& EntitiesManager::Initialize(
    unsigned char* memory_ptr, entity::EntitiesIdContainer& entities_id_container) {
  if (instance_ == nullptr) {
    instance_ = new (memory_ptr) EntitiesManager(entities_id_container);
  }

  return *instance_;
}

EntitiesManager::EntitiesManager(entity::EntitiesIdContainer& entities_id_container)
    : entities_id_container_(entities_id_container), entities_counter_(0) {
}

EntityId EntitiesManager::CreateEntity() {
  EntityId new_id = ++entities_counter_;
  entities_id_container_.Insert(new_id);
  return new_id;
}

void EntitiesManager::RemoveEntity(const EntityId& entity_id) {
  entities_id_container_.Remove(entity_id);
}

void EntitiesManager::Destroy() {
  instance_ = nullptr;
}

}  // namespace manager
}  // namespace ecs