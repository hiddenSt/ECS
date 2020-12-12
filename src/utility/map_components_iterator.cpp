#include "utility/map_components_iterator.hpp"

void ecs::util::MapComponentsIterator::First() {
  auto it = map_.begin();
}

void ecs::util::MapComponentsIterator::Next() {
}

bool ecs::util::MapComponentsIterator::IsDone() {
  return false;
}
