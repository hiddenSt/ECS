#ifndef ECS_INCLUDE_COMPONENTS_MANAGER_HPP_
#define ECS_INCLUDE_COMPONENTS_MANAGER_HPP_

#include <vector>

#include "component_type_container.hpp"
#include "component_type_iterator.hpp"
#include "components_container.hpp"

namespace ecs {

class ComponentsManager {
 public:
  explicit ComponentsManager(const size_t number_of_components_types);

  void AddComponentContainer(ComponentsContainer* components_container);

  template <typename T, typename... Args>
  T* AddComponent(const EntityId& entity_id, Args&&... args);

  template <typename T>
  T* GetComponent(const EntityId& entity_id);

  template <typename T>
  void RemoveComponent(const EntityId& entity_id);

  template <typename T>
  ComponentTypeIterator<T>* GetComponentsIterator();

 private:
  std::vector<ComponentsContainer*> components_types_containers_;
};

template <typename T, typename... Args>
T* ComponentsManager::AddComponent(const EntityId& entity_id, Args&&... args) {
  const ComponentTypeId kGetComponentTypeId = T::StaticGetComponentTypeId();
  Component* new_component =
      components_types_containers_[kGetComponentTypeId - 1]->AddComponent(entity_id);
  if (new_component == nullptr) {
    return nullptr;
  }
  T* new_type_component = new (new_component) T(std::forward<Args>(args)...);
  new_type_component->SetEntityId(entity_id);
  return new_type_component;
}

template <typename T>
T* ComponentsManager::GetComponent(const EntityId& entity_id) {
  const ComponentTypeId kGetComponentTypeId = T::StaticGetComponentTypeId();
  Component* requested_component =
      components_types_containers_[kGetComponentTypeId - 1]->GetComponent(entity_id);
  if (requested_component == nullptr) {
    return nullptr;
  }

  return static_cast<T*>(requested_component);
}

template <typename T>
void ComponentsManager::RemoveComponent(const EntityId& entity_id) {
  const ComponentTypeId kStaticGetComponentTypeId = T::StaticGetComponentTypeId();
  components_types_containers_[kStaticGetComponentTypeId - 1]->RemoveComponent(entity_id);
}

ComponentsManager::ComponentsManager(const size_t number_of_components_types)
    : components_types_containers_(number_of_components_types, nullptr) {
}

void ComponentsManager::AddComponentContainer(ComponentsContainer* components_container) {
  const ComponentTypeId kComponentTypeId = components_container->GetComponentTypeId();
  if (kComponentTypeId > components_types_containers_.size()) {
    throw std::logic_error("Wrong ID");
  }
  components_types_containers_[kComponentTypeId - 1] = components_container;
}

/*template <typename T>
ComponentTypeIterator<T>* ComponentsManager::GetComponentsIterator() {
  const ComponentTypeId component_type_id = T::StaticGetComponentTypeId();
  ComponentIterator* iterator =
      components_types_containers_[component_type_id]->GetComponentsIterator();
  return static_cast<ComponentTypeIterator<T>*>(iterator);
}*/

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENTS_MANAGER_HPP_
