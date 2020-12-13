#include "components_manager.hpp"

ecs::ComponentsManager* ecs::ComponentsManager::instance_ = nullptr;

ecs::ComponentsManager::ComponentsManager(const size_t& number_of_components_types)
    : components_types_containers_(number_of_components_types, nullptr) {
}

void ecs::ComponentsManager::Initialize(unsigned char* memory_ptr,
                                   const size_t& number_of_components_types) {
  if (instance_ != nullptr) {
    return;
  }

  instance_ = new (memory_ptr) ComponentsManager(number_of_components_types);
}

ecs::ComponentsManager& ecs::ComponentsManager::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error(
        "ComponentsManager has to be initialize before using it. Call "
        "ComponentManager::Initialize(unsigned char* memory, const std::size_t& "
        "components_types_count))");
  }
  return *instance_;
}

void ecs::ComponentsManager::Destroy() {
  instance_->~ComponentsManager();
  instance_ = nullptr;
}

void ecs::ComponentsManager::AddComponentContainer(ComponentsContainer* components_container) {
  const ComponentTypeId kComponentTypeId = components_container->GetComponentTypeId();
  components_types_containers_[kComponentTypeId - 1] = components_container;
}
