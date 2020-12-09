#ifndef ECS_INCLUDE_COMPONENT_TYPE_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_HPP_

#include "component.hpp"

namespace ecs {

template <typename T>
class ComponentType : public Component {
 public:
  static const std::size_t StaticGetComponentTypeId() noexcept;

  const std::size_t GetComponentTypeId() const noexcept override;

 private:
  static const std::size_t COMPONENT_TYPE_ID_;
};

template <typename T>
const std::size_t ecs::ComponentType<T>::COMPONENT_TYPE_ID_ = Component::SetComponentTypeId<T>();

template <typename T>
const std::size_t ComponentType<T>::GetComponentTypeId() const noexcept {
  return COMPONENT_TYPE_ID_;
}

template <typename T>
const std::size_t ComponentType<T>::StaticGetComponentTypeId() noexcept {
  return COMPONENT_TYPE_ID_;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_HPP_
