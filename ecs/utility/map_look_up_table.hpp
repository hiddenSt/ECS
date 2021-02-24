#ifndef ECS_INCLUDE_UTILITY_MAP_LOOK_UP_TABLE_HPP_
#define ECS_INCLUDE_UTILITY_MAP_LOOK_UP_TABLE_HPP_

#include <ecs/component/components_look_up_table.hpp>
#include <map>

namespace ecs {
namespace util {

class MapLookUpTable : public component::ComponentsLookUpTable {
 public:
  explicit MapLookUpTable() = default;

  void Insert(const EntityId& entity_id, component::Component* component) override;
  void Remove(const EntityId& entity_id) override;
  component::Component* Find(const EntityId& entity_id) override;
  iterator::ComponentsIterator* GetIterator() override;

 private:
  std::map<EntityId, component::Component*> look_up_table_;
};

}  // namespace util
}  // namespace ecs

#endif  // ECS_INCLUDE_UTILITY_MAP_LOOK_UP_TABLE_HPP_
