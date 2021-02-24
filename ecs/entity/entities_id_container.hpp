#ifndef ECS_INCLUDE_ENTITIES_ID_CONTAINER_HPP_
#define ECS_INCLUDE_ENTITIES_ID_CONTAINER_HPP_

#include <ecs/types.hpp>

namespace ecs {
namespace entity {

class EntitiesIdContainer {
 public:
  virtual void Insert(const EntityId& entity_id) = 0;
  virtual void Remove(const EntityId& entity_id) = 0;
};

}  // namespace entity
}  // namespace ecs

#endif  // ECS_INCLUDE_ENTITIES_ID_CONTAINER_HPP_
