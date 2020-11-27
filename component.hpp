#ifndef ECS__COMPONENT_HPP_
#define ECS__COMPONENT_HPP_

#include "i_component.hpp"
#include "types.hpp"

namespace ecs {

template <typename ComponentType>
class Component : public IComponent {
 public:
  virtual ~Component();

  ComponentTypeId GetComponentTypeId() const noexcept override;
  static ComponentTypeId GetTypeId() noexcept;

 private:
  static const std::size_t kComponentTypeId_;
};

// ComponentType initialization
template <typename ComponentType>
const std::size_t Component<ComponentType>::kComponentTypeId_ =
    1;  // TODO: needs to generate unique id for every ComponentType

template <typename ComponentType>
ComponentTypeId Component<ComponentType>::GetComponentTypeId() const noexcept {
  return kComponentTypeId_;
}

template <typename ComponentType>
Component<ComponentType>::~Component() {
  // TODO: need to throw exception
}

template <typename ComponentType>
ComponentTypeId Component<ComponentType>::GetTypeId() noexcept {
  return kComponentTypeId_;
}

}  // namespace ecs

#endif  // ECS__COMPONENT_HPP_
