#include <ecs/manager/components_manager.hpp>

namespace ecs {
namespace manager {

ComponentsManager* ComponentsManager::instance_ = nullptr;

void ComponentsManager::Initialize(unsigned char* memory_ptr,
                                   const size_t& number_of_components_types) {
  if (instance_ != nullptr) {
    return;
  }
  instance_ = new (memory_ptr) ComponentsManager(number_of_components_types);
}

void ComponentsManager::Destroy() {
  for (auto component_type_container : instance_->components_types_containers_) {
    if (component_type_container != nullptr) {
      component_type_container->~ComponentsContainer();
    }
  }
  instance_->~ComponentsManager();
  instance_ = nullptr;
}

ComponentsManager::ComponentsManager(const size_t& number_of_components_types)
    : components_types_containers_(number_of_components_types, nullptr) {
}

ComponentsManager& ComponentsManager::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error(
        "ComponentsManager has to be initialize before using it. Call "
        "ComponentManager::Initialize(unsigned char* memory, const std::size_t& "
        "components_types_count))");
  }
  return *instance_;
}

void ComponentsManager::AddComponentsContainer(
    component::ComponentsContainer* components_container) {
  const ComponentTypeId kComponentTypeId = components_container->GetComponentTypeId();
  components_types_containers_[kComponentTypeId - 1] = components_container;
}

void ComponentsManager::RemoveEntitiesComponents(const EntityId& entity_id) {
  for (auto* container : components_types_containers_) {
    if (container != nullptr && container->GetComponent(entity_id) != nullptr) {
      container->RemoveComponent(entity_id);
    }
  }
}

}  // namespace manager
}  // namespace ecs