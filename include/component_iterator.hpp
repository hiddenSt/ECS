#ifndef ECS_INCLUDE_COMPONENT_ITERATOR_HPP_
#define ECS_INCLUDE_COMPONENT_ITERATOR_HPP_

#include "component.hpp"

namespace ecs {

class ComponentIterator {
 public:
  virtual void First() = 0;
  virtual bool IsDone() = 0;
  virtual void Next() = 0;
};

}  // namespace ecs
#endif  // ECS_INCLUDE_COMPONENT_ITERATOR_HPP_
