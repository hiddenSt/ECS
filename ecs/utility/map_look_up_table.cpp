#include <ecs/utility/map_components_iterator.hpp>
#include <ecs/utility/map_look_up_table.hpp>

namespace ecs {
namespace util {

void MapLookUpTable::Insert(const EntityId &entity_id, component::Component *component) {
  look_up_table_.insert(std::make_pair(entity_id, component));
}

void MapLookUpTable::Remove(const EntityId &entity_id) {
  look_up_table_.erase(entity_id);
}

component::Component *MapLookUpTable::Find(const EntityId &entity_id) {
  auto search = look_up_table_.find(entity_id);
  if (search == look_up_table_.end()) {
    return nullptr;
  }
  return search->second;
}

iterator::ComponentsIterator *MapLookUpTable::GetIterator() {
  iterator::ComponentsIterator *iterator = new MapComponentsIterator(look_up_table_);
  return iterator;
}

}  // namespace util
}  // namespace ecs