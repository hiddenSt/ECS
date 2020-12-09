#include "component.hpp"

std::size_t ecs::Component::components_types_counter = 0;

std::size_t ecs::Component::GetEntityId() const noexcept {
  return entity_id_;
}

const std::size_t ecs::Component::GetComponentsTypesCount() {
  return components_types_counter;
}

void ecs::Component::SetEntityId(const std::size_t& entity_id) noexcept {
  entity_id_ = entity_id;
}

ecs::Component::Component() noexcept : entity_id_(0) {
}