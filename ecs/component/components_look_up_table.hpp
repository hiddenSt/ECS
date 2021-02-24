#ifndef ECS_INCLUDE_COMPONENTS_LOOK_UP_TABLE_HPP_
#define ECS_INCLUDE_COMPONENTS_LOOK_UP_TABLE_HPP_

#include <ecs/component/component.hpp>
#include <ecs/iterator/components_iterator.hpp>
#include <ecs/types.hpp>

namespace ecs {
namespace component {

class ComponentsLookUpTable {
 public:
  virtual void Insert(const EntityId& entity_id, Component* component) = 0;
  virtual void Remove(const EntityId& entity_id) = 0;
  virtual Component* Find(const EntityId& entity_id) = 0;
  virtual iterator::ComponentsIterator* GetIterator() = 0;
};

}  // namespace component
}  // namespace ecs
#endif  // ECS_INCLUDE_COMPONENTS_LOOK_UP_TABLE_HPP_
