#include "component.hpp"

std::size_t ecs::Component::components_types_counter_ = 0;

ecs::EntityId ecs::Component::GetEntityId() const noexcept {
  return entity_id_;
}

void ecs::Component::SetEntityId(const ecs::EntityId& entity_id) noexcept {
  entity_id_ = entity_id;
}

ecs::Component::Component() noexcept : entity_id_(0) {
}

std::size_t ecs::Component::GetComponentsTypesCount() {
  return components_types_counter_;
}