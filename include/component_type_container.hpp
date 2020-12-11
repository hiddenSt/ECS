#ifndef ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_

#include <map>
#include <stdexcept>
#include <utility>

#include "components_container.hpp"

namespace ecs {

template <typename T, typename Alloc, typename MapAlloc>
class ComponentTypeContainer : public ComponentsContainer {
 public:
  explicit ComponentTypeContainer(Alloc& alloc, MapAlloc& map_alloc);

  Component* AddComponent(const EntityId& entity_id) override;
  Component* GetComponent(const EntityId& entity_id) override;
  void RemoveComponent(const EntityId& entity_id) override;
  ComponentIterator* GetComponentsIterator();

 private:
  Alloc& alloc_;
  MapAlloc& map_alloc_;
  std::map<EntityId, T*, std::less<EntityId>, MapAlloc> entity_lookup_table_;
};

template <typename T, typename Alloc, typename MapAlloc>
Component* ComponentTypeContainer<T, Alloc, MapAlloc>::GetComponent(const EntityId& entity_id) {
  auto search = entity_lookup_table_.find(entity_id);
  if (search == entity_lookup_table_.end()) {
    return nullptr;
  }

  return search->second;
}

template <typename T, typename Alloc, typename MapAlloc>
void ComponentTypeContainer<T, Alloc, MapAlloc>::RemoveComponent(const EntityId& entity_id) {
  auto component = entity_lookup_table_.find(entity_id);

  if (component == entity_lookup_table_.end()) {
    throw std::logic_error("Can not remove component because entity does not has one");
  }

  alloc_.Free(component->second);
  entity_lookup_table_.erase(entity_id);
}

template <typename T, typename Alloc, typename MapAlloc>
ComponentTypeContainer<T, Alloc, MapAlloc>::ComponentTypeContainer(Alloc& alloc,
                                                                   MapAlloc& map_alloc)
    : ComponentsContainer(T::StaticGetComponentTypeId()),
      alloc_(alloc),
      map_alloc_(map_alloc),
      entity_lookup_table_(map_alloc) {
}

template <typename T, typename Alloc, typename MapAlloc>
ComponentIterator* ComponentTypeContainer<T, Alloc, MapAlloc>::GetComponentsIterator() {
}

template <typename T, typename Alloc, typename MapAlloc>
Component* ComponentTypeContainer<T, Alloc, MapAlloc>::AddComponent(const EntityId& entity_id) {
  auto component = entity_lookup_table_.find(entity_id);
  if (component != entity_lookup_table_.end()) {
    throw std::logic_error("Entity already has component of this type");
  }
  auto* new_component_memory = alloc_.Allocate();
  if (new_component_memory == nullptr) {
    throw std::logic_error("Can not allocate memory for component");
  }
  auto new_comp = static_cast<T*>(new_component_memory);
  entity_lookup_table_.insert(std::make_pair(entity_id, new_comp));
  return static_cast<Component*>(new_comp);
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
