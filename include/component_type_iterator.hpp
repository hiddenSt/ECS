#ifndef ECS_INCLUDE_COMPONENT_TYPE_ITERATOR_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_ITERATOR_HPP_

#include "types.hpp"

#include "components_container.hpp"

namespace ecs {

template <typename T>
class ComponentTypeIterator {
 public:
  explicit ComponentTypeIterator(ComponentsIterator& iterator);

  void First();
  bool IsDone();
  void Next();
  T* GetCurrentComponent();

 private:
  ComponentsIterator& iterator_;
};

template <typename T>
ComponentTypeIterator<T>::ComponentTypeIterator(ComponentsIterator& iterator) : iterator_(iterator_) {
}
template <typename T>
void ComponentTypeIterator<T>::First() {
  iterator_.First();
}
template <typename T>
bool ComponentTypeIterator<T>::IsDone() {
  return iterator_.IsDone();
}

template <typename T>
void ComponentTypeIterator<T>::Next() {
  iterator_.Next();
}

template <typename T>
T* ComponentTypeIterator<T>::GetCurrentComponent() {
  return static_cast<T*>(iterator_.CurrentComponent());
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_ITERATOR_HPP_
