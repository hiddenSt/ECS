#ifndef ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_

#include <map>
#include <utility>

#include "components_container.hpp"

namespace ecs {

template <typename T, typename Alloc, typename MapAlloc>
class ComponentTypeContainer : ComponentsContainer {
 public:
  explicit ComponentTypeContainer(const Alloc& alloc, const MapAlloc& map_alloc);

  Component* GetComponent(const std::size_t& entity_id) override;
  Component* AddComponent(const std::size_t& entity_id) override;
  void RemoveComponent(const std::size_t& entity_id) override;
  ComponentIterator* GetComponentsIterator() override;

 private:
  Alloc& alloc_;
  MapAlloc& map_alloc_;
  std::map<std::size_t, T*, std::less<std::size_t>, MapAlloc> entity_lookup_table_;
};

template <typename T, typename Alloc, typename MapAlloc>
Component* ComponentTypeContainer<T, Alloc, MapAlloc>::GetComponent(const size_t& entity_id) {
  return entity_lookup_table_.find(entity_id);
}

template <typename T, typename Alloc, typename MapAlloc>
Component* ComponentTypeContainer<T, Alloc, MapAlloc>::AddComponent(const size_t& entity_id) {
  auto* new_comp = alloc_.Allocate();
  new_comp = new (new_comp) T();
  entity_lookup_table_.insert(std::make_pair(entity_id, new_comp));
  return new_comp;
}

template <typename T, typename Alloc, typename MapAlloc>
void ComponentTypeContainer<T, Alloc, MapAlloc>::RemoveComponent(const size_t& entity_id) {
  auto comp_pair = entity_lookup_table_.find(entity_id);
  alloc_.Free(comp_pair->seccond);
  entity_lookup_table_.erase(entity_id);
}

template <typename T, typename Alloc, typename MapAlloc>
ComponentTypeContainer<T, Alloc, MapAlloc>::ComponentTypeContainer(const Alloc& alloc,
                                                                   const MapAlloc& map_alloc)
    : alloc_(alloc),
      map_alloc_(std::map<std::size_t, T*, std::less<std::size_t>, MapAlloc>(map_alloc)) {
}

template <typename T, typename Alloc, typename MapAlloc>
ComponentIterator* ComponentTypeContainer<T, Alloc, MapAlloc>::GetComponentsIterator() {

}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
