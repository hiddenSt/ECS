#ifndef ECS_INCLUDE_COMPONENTS_MANAGER_HPP_
#define ECS_INCLUDE_COMPONENTS_MANAGER_HPP_

#include <vector>

#include "component_type_iterator.hpp"
#include "components_container.hpp"

namespace ecs {

class ComponentsManager {
 public:
  template <typename T, typename... Args>
  T* AddComponent(const std::size_t& entity_id, Args&&... args);

  template <typename T>
  T* GetComponent(const std::size_t& entity_id);

  template <typename T>
  void RemoveComponent(const size_t& entity_id);

  template <typename T>
  ComponentTypeIterator<T>* GetComponentsIterator();

 private:
  std::vector<ComponentsContainer*> components_types_containers_;
};

template <typename T, typename... Args>
T* ComponentsManager::AddComponent(const size_t& entity_id, Args&&... args) {
  const std::size_t component_type_id = T::StaticGetComponentTypeId();
  Component* new_component =
      components_types_containers_[component_type_id]->AddComponent(entity_id);
  return static_cast<T*>(new_component);
}

template <typename T>
T* ComponentsManager::GetComponent(const size_t& entity_id) {
  const std::size_t component_type_id = T::StaticGetComponentTypeId();
  Component* requested_component =
      components_types_containers_[component_type_id]->GetComponent(entity_id);
  if (requested_component == nullptr) {
    return nullptr;
  }

  return static_cast<T*>(requested_component);
}

template <typename T>
void ComponentsManager::RemoveComponent(const size_t& entity_id) {
  const std::size_t component_type_id = T::StaticGetComponentTypeId();
  components_types_containers_[component_type_id]->RemoveComponent(entity_id);
}

template <typename T>
ComponentTypeIterator<T>* ComponentsManager::GetComponentsIterator() {
  const std::size_t component_type_id = T::StaticGetComponentTypeId();
  ComponentIterator* iterator =
      components_types_containers_[component_type_id]->GetComponentsIterator();
  return static_cast<ComponentTypeIterator<T>*>(iterator);
}

}  // namespace ecs
#endif  // ECS_INCLUDE_COMPONENTS_MANAGER_HPP_
