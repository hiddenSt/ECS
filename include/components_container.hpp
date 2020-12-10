#ifndef ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_

#include "component.hpp"
#include "component_iterator.hpp"

namespace ecs {

class ComponentsContainer {
 public:
  explicit ComponentsContainer(const ComponentTypeId& component_type_id) noexcept;

  virtual Component* GetComponent(const EntityId& entity_id) = 0;
  virtual Component* AddComponent(const EntityId& entity_id) = 0;
  virtual void RemoveComponent(const EntityId& entity_id) = 0;
  virtual ComponentIterator* GetComponentsIterator() = 0;

  const ComponentTypeId GetComponentTypeId() const noexcept;

 protected:
  const ComponentTypeId COMPONENT_TYPE_ID_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_
