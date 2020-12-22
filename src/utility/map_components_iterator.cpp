#include "utility/map_components_iterator.hpp"

ecs::util::MapComponentsIterator::MapComponentsIterator(std::map<EntityId, Component*>& map)
    : map_(map) {
}

void ecs::util::MapComponentsIterator::First() {
  iterator_ = map_.begin();
}

void ecs::util::MapComponentsIterator::Next() {
  iterator_++;
}

bool ecs::util::MapComponentsIterator::IsDone() {
  return iterator_ == map_.end();
}

ecs::Component* ecs::util::MapComponentsIterator::CurrentComponent() {
  return iterator_->second;
}
