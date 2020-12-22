#ifndef ECS_INCLUDE_ENTITIES_MANAGER_HPP_
#define ECS_INCLUDE_ENTITIES_MANAGER_HPP_

#include "entities_id_container.hpp"

namespace ecs {

class EntitiesManager {
 public:
  static EntitiesManager& Instance();
  static EntitiesManager& Create(EntitiesIdContainer& entities_id_container);

  EntityId CreateEntity();
  void RemoveEntity(const EntityId& entity_id);

 private:
  EntitiesManager(EntitiesIdContainer& entities_id_container);

  EntitiesIdContainer& entities_id_container_;
  std::size_t entities_counter_;
  static EntitiesManager* instance_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_ENTITIES_MANAGER_HPP_
