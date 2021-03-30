#ifndef ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
#define ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_

#include <map>
#include <stdexcept>
#include <utility>

#include <ecs/component/components_container.hpp>
#include <ecs/component/components_look_up_table.hpp>

namespace ecs {
namespace component {

template <typename T, typename Alloc>
class ComponentTypeContainer : public ComponentsContainer {
 public:
  explicit ComponentTypeContainer(Alloc& alloc, ComponentsLookUpTable& components_look_up_table);
  ~ComponentTypeContainer();

  Component* AddComponent(const EntityId& entity_id) override;
  Component* GetComponent(const EntityId& entity_id) override;
  void RemoveComponent(const EntityId& entity_id) override;
  iterator::ComponentsIterator* GetComponentsIterator() override;

 private:
  Alloc& alloc_;
  ComponentsLookUpTable& components_lookup_table_;
};

template <typename T, typename Alloc>
Component* ComponentTypeContainer<T, Alloc>::GetComponent(const EntityId& entity_id) {
  auto* search = components_lookup_table_.Find(entity_id);
  return search;
}

template <typename T, typename Alloc>
void ComponentTypeContainer<T, Alloc>::RemoveComponent(const EntityId& entity_id) {
  auto* component = components_lookup_table_.Find(entity_id);

  if (component == nullptr) {
    throw std::logic_error("Can not remove component because entity does not has one.");
  }

  alloc_.Free(component);
  components_lookup_table_.Remove(entity_id);
}

template <typename T, typename Alloc>
ComponentTypeContainer<T, Alloc>::ComponentTypeContainer(Alloc& alloc,
                                                         ComponentsLookUpTable& look_up_table)
    : ComponentsContainer(T::StaticGetComponentTypeId()),
      alloc_(alloc),
      components_lookup_table_(look_up_table) {
}

template <typename T, typename Alloc>
iterator::ComponentsIterator* ComponentTypeContainer<T, Alloc>::GetComponentsIterator() {
  return components_lookup_table_.GetIterator();
}

template <typename T, typename Alloc>
Component* ComponentTypeContainer<T, Alloc>::AddComponent(const EntityId& entity_id) {
  auto component = components_lookup_table_.Find(entity_id);
  if (component != nullptr) {
    throw std::logic_error("Entity already has component of this type");
  }
  auto* new_component_memory = alloc_.Allocate();
  if (new_component_memory == nullptr) {
    throw std::logic_error("Can not allocate memory for component");
  }
  auto new_comp = static_cast<T*>(new_component_memory);
  components_lookup_table_.Insert(entity_id, new_comp);
  return static_cast<Component*>(new_comp);
}

template <typename T, typename Alloc>
ComponentTypeContainer<T, Alloc>::~ComponentTypeContainer() {
  auto* iterator = components_lookup_table_.GetIterator();
  for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
    alloc_.Free(iterator->CurrentComponent());
  }
}

}  // namespace component
}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_TYPE_CONTAINER_HPP_
