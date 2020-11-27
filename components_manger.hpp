#ifndef ECS__COMPONENTS_MANGER_HPP_
#define ECS__COMPONENTS_MANGER_HPP_

#include <map>
#include <vector>

#include "i_component.hpp"
#include "i_component_container.hpp"
#include "types.hpp"

namespace ecs {

class ComponentsManger {
 public:
  template <typename ComponentType, typename... Args>
  IComponent* AddComponent(const EntityId& entity_id, Args&&... args);

  template <typename ComponentType>
  void RemoveComponent(const EntityId& entity_id);

  template <typename ComponentType>
  IComponent* GetComponent(const EntityId& entity_id);

 private:
  std::map<ComponentContainerId, IComponentContainer*, std::less<ComponentContainerId>> containers_;
  std::vector<std::vector<IComponent*>> entities_;
};

template <typename ComponentType, typename... Args>
IComponent* ComponentsManger::AddComponent(const EntityId& entity_id, Args&&... args) {
  auto component_container = containers_.find(ComponentType::GetTypeId());

  if (component_container == nullptr) {
  }

  component_container->second->
  return nullptr;
}

template <typename ComponentType>
void ComponentsManger::RemoveComponent(const EntityId& entity_id) {
}

template <typename ComponentType>
IComponent* ComponentsManger::GetComponent(const EntityId& entity_id) {
  return nullptr;
}

}  // namespace ecs

#endif  // ECS__COMPONENTS_MANGER_HPP_
