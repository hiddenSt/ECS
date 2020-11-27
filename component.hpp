#ifndef ECS__COMPONENT_HPP_
#define ECS__COMPONENT_HPP_

#include "i_component.hpp"

namespace ecs {

template <typename ComponentType>
class Component : public IComponent {
 public:
  std::size_t GetComponentTypeId() const noexcept override;

 private:
  static const std::size_t component_type_id_;
};

template <typename ComponentType>
std::size_t Component<ComponentType>::GetComponentTypeId() const noexcept {
  return component_type_id_;
}

}  // namespace ecs

#endif  // ECS__COMPONENT_HPP_
