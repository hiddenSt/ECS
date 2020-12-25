#ifndef ECS_INCLUDE_COMPONENTS_MANAGER_HPP_
#define ECS_INCLUDE_COMPONENTS_MANAGER_HPP_

#include <vector>

#include "component_type_container.hpp"
#include "component_type_iterator.hpp"
#include "components_container.hpp"

namespace ecs {

class ComponentsManager {
 public:
  static void Initialize(unsigned char* memory_ptr, const size_t& number_of_components_types);
  static ComponentsManager& Instance();
  static void Destroy();

  explicit ComponentsManager(ComponentsManager&& other) = delete;
  explicit ComponentsManager(const ComponentsManager& other) = delete;
  ComponentsManager& operator=(ComponentsManager&& other) = delete;
  ComponentsManager& operator=(const ComponentsManager& other) = delete;

  void AddComponentsContainer(ComponentsContainer* components_container);
  template <typename T, typename... Args>
  T* AddComponent(const EntityId& entity_id, Args&&... args);
  template <typename T>
  T* GetComponent(const EntityId& entity_id);
  template <typename T>
  void RemoveComponent(const EntityId& entity_id);
  void RemoveEntitiesComponents(const EntityId& entity_id);
  template <typename T>
  ComponentTypeIterator<T>* GetComponentsIterator();
  template <typename T>
  void DestroyComponentTypeIterator(ComponentTypeIterator<T>* iterator);

 private:
  explicit ComponentsManager(const size_t& number_of_components_types);
  ~ComponentsManager() = default;

  static ComponentsManager* instance_;
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
  const ComponentTypeId kComponentTypeId = T::StaticGetComponentTypeId();
  components_types_containers_[kComponentTypeId - 1]->RemoveComponent(entity_id);
}

template <typename T>
ComponentTypeIterator<T>* ComponentsManager::GetComponentsIterator() {
  const ComponentTypeId kComponentTypeId = T::StaticGetComponentTypeId();

  ComponentsIterator* iterator =
      components_types_containers_[kComponentTypeId - 1]->GetComponentsIterator();
  ComponentTypeIterator<T>* component_type_iterator = new ComponentTypeIterator<T>(iterator);
  return component_type_iterator;
}

template <typename T>
void ComponentsManager::DestroyComponentTypeIterator(ComponentTypeIterator<T>* iterator) {
  delete iterator;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENTS_MANAGER_HPP_
