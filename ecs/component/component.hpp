#ifndef ECS_INCLUDE_COMPONENT_HPP_
#define ECS_INCLUDE_COMPONENT_HPP_

#include <ecs/types.hpp>

namespace ecs {
namespace component {

class Component {
 public:
  explicit Component() noexcept;
  virtual ~Component() = default;

  template <typename ConcreteComponentType>
  static ComponentTypeId SetComponentTypeId();
  static std::size_t GetComponentsTypesCount();
  void SetEntityId(const EntityId& entity_id) noexcept;
  virtual ComponentTypeId GetComponentTypeId() const noexcept = 0;
  EntityId GetEntityId() const noexcept;

 private:
  static std::size_t components_types_counter_;
  EntityId entity_id_;
};

template <typename ConcreteComponentType>
ComponentTypeId Component::SetComponentTypeId() {
  static ComponentTypeId new_type_id = ++components_types_counter_;
  return new_type_id;
}

}  // namespace component
}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_HPP_
