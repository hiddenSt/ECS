#ifndef ECS__I_COMPONENT_CONTAINER_HPP_
#define ECS__I_COMPONENT_CONTAINER_HPP_

#include "i_component.hpp"
#include "types.hpp"

namespace ecs {

class IComponentContainer {
 public:
  virtual ComponentContainerId GetComponentContainerId() = 0;
  virtual IComponent* GetComponent(const EntityId& entity_id) = 0;
  virtual IComponent* AddComponent(const EntityId& entity_id) = 0;
};

}  // namespace ecs

#endif  // ECS__I_COMPONENT_CONTAINER_HPP_
