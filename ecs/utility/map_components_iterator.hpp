#ifndef ECS_INCLUDE_UTILITY_MAP_COMPONENTS_ITERATOR_HPP_
#define ECS_INCLUDE_UTILITY_MAP_COMPONENTS_ITERATOR_HPP_

#include <map>

#include <ecs/iterator/components_iterator.hpp>

namespace ecs {
namespace util {

class MapComponentsIterator : public iterator::ComponentsIterator {
 public:
  explicit MapComponentsIterator(std::map<EntityId, component::Component*>& map);
  void First() override;
  void Next() override;
  bool IsDone() override;
  component::Component* CurrentComponent() override;

 private:
  std::map<EntityId, component::Component*>& map_;
  std::map<EntityId, component::Component*>::iterator iterator_;
};

}  // namespace util
}  // namespace ecs

#endif  // ECS_INCLUDE_UTILITY_MAP_COMPONENTS_ITERATOR_HPP_
