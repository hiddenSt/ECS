#ifndef ECS_INCLUDE_UTILITY_MAP_COMPONENTS_ITERATOR_HPP_
#define ECS_INCLUDE_UTILITY_MAP_COMPONENTS_ITERATOR_HPP_

#include "components_iterator.hpp"
#include <map>

namespace ecs {
namespace util {

class MapComponentsIterator : public ComponentsIterator {
 public:
  explicit MapComponentsIterator(std::map<EntityId, Component*>& map);
  void First() override;
  void Next() override;
  bool IsDone() override;
  Component* CurrentComponent() override;

 private:
  std::map<EntityId, Component*>& map_;
  
};

}  // namespace util
}  // namespace ecs



#endif  // ECS_INCLUDE_UTILITY_MAP_COMPONENTS_ITERATOR_HPP_