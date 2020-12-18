#include "utility/map_look_up_table.hpp"
#include "utility/map_components_iterator.hpp"

void ecs::util::MapLookUpTable::Insert(const ecs::EntityId &entity_id, ecs::Component *component) {
  look_up_table_.insert(std::make_pair(entity_id, component));
}

void ecs::util::MapLookUpTable::Remove(const ecs::EntityId &entity_id) {
  look_up_table_.erase(entity_id);
}

ecs::Component *ecs::util::MapLookUpTable::Find(const ecs::EntityId &entity_id) {
  auto search = look_up_table_.find(entity_id);
  if (search == look_up_table_.end()) {
    return nullptr;
  }
  return search->second;
}

ecs::ComponentsIterator* ecs::util::MapLookUpTable::GetIterator() {
  ComponentsIterator* iterator = new MapComponentsIterator(look_up_table_);
  return iterator;
}
