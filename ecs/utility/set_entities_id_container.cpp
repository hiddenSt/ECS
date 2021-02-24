#include <ecs/utility/set_entities_id_container.hpp>

#include <stdexcept>

namespace ecs {
namespace util {

void SetEntitiesIdContainer::Insert(const EntityId& entity_id) {
  if (entities_set_.find(entity_id) != entities_set_.end()) {
    throw std::logic_error("Entity with this id already exist.");
  }
  entities_set_.insert(entity_id);
}

void SetEntitiesIdContainer::Remove(const EntityId& entity_id) {
  entities_set_.erase(entity_id);
}

}  // namespace util
}  // namespace ecs