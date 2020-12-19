#include "utility/set_entities_id_container.hpp"
#include <stdexcept>

void ecs::util::SetEntitiesIdContainer::Insert(const ecs::EntityId& entity_id) {
  if (entities_set_.find(entity_id) != entities_set_.end()) {
    throw std::logic_error("Entity with this id already exist.");
  }
  entities_set_.insert(entity_id);
}

void ecs::util::SetEntitiesIdContainer::Remove(const ecs::EntityId& entity_id) {
  entities_set_.erase(entity_id);
}
