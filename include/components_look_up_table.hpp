#ifndef ECS_INCLUDE_COMPONENTS_LOOK_UP_TABLE_HPP_
#define ECS_INCLUDE_COMPONENTS_LOOK_UP_TABLE_HPP_

#include "component.hpp"
#include "types.hpp"

namespace ecs {

class ComponentsLookUpTable {
 public:
  virtual void Insert(const EntityId& entity_id, Component* component) = 0;
  virtual void Remove(const EntityId& entity_id) = 0;
  virtual Component* Find(const EntityId& entity_id) = 0;
};

}  // namespace ecs
#endif  // ECS_INCLUDE_COMPONENTS_LOOK_UP_TABLE_HPP_
