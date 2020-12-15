#ifndef ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_

#include "component.hpp"
#include "components_iterator.hpp"

namespace ecs {

class ComponentsContainer {
 public:
  explicit ComponentsContainer(const ComponentTypeId& component_type_id) noexcept;
  virtual ~ComponentsContainer() = default;

  ComponentTypeId GetComponentTypeId() const noexcept;
  virtual Component* AddComponent(const EntityId& entity_id) = 0;
  virtual Component* GetComponent(const EntityId& entity_id) = 0;
  virtual void RemoveComponent(const EntityId& entity_id) = 0;
  virtual ComponentsIterator* GetComponentsIterator() = 0;

 protected:
  const ComponentTypeId kComponentTypeId_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_
