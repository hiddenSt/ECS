#ifndef ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_

#include "component.hpp"
#include "component_iterator.hpp"

namespace ecs {

class ComponentsContainer {
 public:
  explicit ComponentsContainer(const std::size_t& component_type_id) noexcept;

  virtual Component* GetComponent(const std::size_t& entity_id) = 0;
  virtual Component* AddComponent(const std::size_t& entity_id) = 0;
  virtual void RemoveComponent(const std::size_t& entity_id) = 0;
  virtual ComponentIterator* GetComponentsIterator() = 0;

  const std::size_t GetComponentTypeId() const noexcept;

 protected:
  const std::size_t COMPONENT_TYPE_ID_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENTS_CONTAINER_HPP_
