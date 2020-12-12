#ifndef ECS_INCLUDE_UTILITY_MAP_LOOK_UP_TABLE_HPP_
#define ECS_INCLUDE_UTILITY_MAP_LOOK_UP_TABLE_HPP_

#include <map>

#include "components_look_up_table.hpp"

namespace ecs {
namespace util {

class MapLookUpTable : public ComponentsLookUpTable {
 public:
  explicit MapLookUpTable() = default;

  void Insert(const EntityId& entity_id, Component* component) override;
  void Remove(const EntityId& entity_id) override;
  Component* Find(const EntityId& entity_id) override;
  ComponentsIterator* GetIterator() override;

 private:
  std::map<EntityId, Component*> look_up_table_;
};

}  // namespace util
}  // namespace ecs

#endif  // ECS_INCLUDE_UTILITY_MAP_LOOK_UP_TABLE_HPP_
