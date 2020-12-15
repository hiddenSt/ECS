#ifndef ECS_INCLUDE_COMPONENT_TYPE_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_HPP_

#include "component.hpp"

namespace ecs {

template <typename ConcreteComponentType>
class ComponentType : public Component {
 public:
  static ComponentTypeId StaticGetComponentTypeId() noexcept;
  ComponentTypeId GetComponentTypeId() const noexcept override;

 private:
  static const ComponentTypeId kComponentTypeId_;
};

template <typename ConcreteComponentType>
const ComponentTypeId ComponentType<ConcreteComponentType>::kComponentTypeId_ =
    Component::SetComponentTypeId<ConcreteComponentType>();

template <typename ConcreteComponentType>
ComponentTypeId ComponentType<ConcreteComponentType>::GetComponentTypeId() const noexcept {
  return kComponentTypeId_;
}

template <typename ConcreteComponentType>
ComponentTypeId ComponentType<ConcreteComponentType>::StaticGetComponentTypeId() noexcept {
  return kComponentTypeId_;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_HPP_
