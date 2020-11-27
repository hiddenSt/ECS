//
// Created by hiddenst on 27.11.2020.
//

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
