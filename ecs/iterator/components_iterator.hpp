#ifndef ECS_INCLUDE_COMPONENTS_ITERATOR_HPP_
#define ECS_INCLUDE_COMPONENTS_ITERATOR_HPP_

#include <ecs/component/component.hpp>

namespace ecs {
namespace iterator {

class ComponentsIterator {
 public:
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
  virtual component::Component* CurrentComponent() = 0;
};

}  // namespace iterator
}  // namespace ecs
#endif  // ECS_INCLUDE_COMPONENTS_ITERATOR_HPP_
