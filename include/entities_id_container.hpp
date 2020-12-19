#ifndef ECS_INCLUDE_ENTITIES_ID_CONTAINER_HPP_
#define ECS_INCLUDE_ENTITIES_ID_CONTAINER_HPP_

#include "types.hpp"

namespace ecs {

class EntitiesIdContainer {
 public:
  virtual void Insert(const EntityId& entity_id) = 0;
  virtual void Remove(const EntityId& entity_id) = 0;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_ENTITIES_ID_CONTAINER_HPP_
