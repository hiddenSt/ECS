#ifndef ECS_INCLUDE_COMPONENTS_ITERATOR_HPP_
#define ECS_INCLUDE_COMPONENTS_ITERATOR_HPP_

#include "component.hpp"

namespace ecs {

class ComponentsIterator {
 public:
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
  virtual Component* CurrentComponent() = 0;
};

}  // namespace ecs
#endif  // ECS_INCLUDE_COMPONENTS_ITERATOR_HPP_
