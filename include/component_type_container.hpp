#ifndef ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_

#include <map>
#include <utility>

#include "components_container.hpp"

namespace ecs {

template <typename T, typename Alloc, typename MapAlloc>
class ComponentTypeContainer : public ComponentsContainer {
 public:
  explicit ComponentTypeContainer(Alloc& alloc, MapAlloc& map_alloc);

  Component* GetComponent(const EntityId& entity_id) override;
  Component* AddComponent(const EntityId& entity_id) override;
  void RemoveComponent(const EntityId& entity_id) override;
  ComponentIterator* GetComponentsIterator() override;

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
Component* ComponentTypeContainer<T, Alloc, MapAlloc>::AddComponent(const EntityId& entity_id) {
  auto* new_comp_memory = alloc_.Allocate();
  auto* new_comp = new (new_comp_memory) T();
  entity_lookup_table_.insert(std::make_pair(entity_id, new_comp));
  return new_comp;
}

template <typename T, typename Alloc, typename MapAlloc>
void ComponentTypeContainer<T, Alloc, MapAlloc>::RemoveComponent(const EntityId& entity_id) {
  auto comp_pair = entity_lookup_table_.find(entity_id);
  alloc_.Free(comp_pair->second);
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

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
