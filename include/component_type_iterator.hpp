#ifndef ECS_INCLUDE_COMPONENT_TYPE_ITERATOR_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_ITERATOR_HPP_

#include <cstdint>

#include "components_container.hpp"

namespace ecs {

template <typename T>
class ComponentTypeIterator : ComponentIterator {
 public:
  explicit ComponentTypeIterator(ComponentsContainer& comp_container);

  void First() override;
  bool IsDone() override;
  void Next() override;
  T* GetCurrentComponent();

 private:
  std::size_t current_component_index_;
  ComponentsContainer& comp_container_;
  T* current_component_;
};

template <typename T>
ComponentTypeIterator<T>::ComponentTypeIterator(ComponentsContainer& comp_container)
    : comp_container_(comp_container), current_component_(nullptr), current_component_index_(0) {
}

template <typename T>
void ComponentTypeIterator<T>::First() {
}

template <typename T>
bool ComponentTypeIterator<T>::IsDone() {
  return false;
}

template <typename T>
T* ComponentTypeIterator<T>::GetCurrentComponent() {
  return current_component_;
}

template <typename T>
void ComponentTypeIterator<T>::Next() {
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_ITERATOR_HPP_
