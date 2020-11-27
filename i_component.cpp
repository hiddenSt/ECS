#include "i_component.hpp"
ecs::IComponent::EntityId ecs::IComponent::GetEntityId() const noexcept {
  return entity_id_;
}
void ecs::IComponent::Activate() noexcept {
  enabled_ = true;
}
void ecs::IComponent::Deactivate() noexcept {
  enabled_ = false;
}
bool ecs::IComponent::IsActive() const noexcept {
  return enabled_;
}
ecs::IComponent::IComponent(const EntityId& entity_id, bool enabled) noexcept
    : entity_id_(entity_id), enabled_(enabled) {
}
ecs::IComponent::~IComponent() {
}
