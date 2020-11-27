#ifndef ECS__COMPONENTS_MANGER_HPP_
#define ECS__COMPONENTS_MANGER_HPP_

#include "i_component.hpp"

namespace ecs {

class ComponentsManger {
 public:
  template <typename ComponentType, typename... Args>
  IComponent AddComponent(const EntityId& entity_id, Args&&... args);

  template <typename ComponentType>
  void RemoveComponent(const EntityId& entity_id);

  template <typename ComponentType>
  IComponent* GetComponent(const EntityId& entity_id);
};

}  // namespace ecs

#endif  // ECS__COMPONENTS_MANGER_HPP_
