#include <ecs/utility/map_components_iterator.hpp>

namespace ecs {
namespace util {

MapComponentsIterator::MapComponentsIterator(std::map<EntityId, component::Component*>& map)
    : map_(map) {
}

void MapComponentsIterator::First() {
  iterator_ = map_.begin();
}

void MapComponentsIterator::Next() {
  iterator_++;
}

bool MapComponentsIterator::IsDone() {
  return iterator_ == map_.end();
}

component::Component* ecs::util::MapComponentsIterator::CurrentComponent() {
  return iterator_->second;
}

}  // namespace util
}  // namespace ecs