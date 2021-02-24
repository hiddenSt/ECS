#include <ecs/component/component.hpp>

namespace ecs {
namespace component {

std::size_t Component::components_types_counter_ = 0;

ecs::EntityId Component::GetEntityId() const noexcept {
  return entity_id_;
}

void Component::SetEntityId(const EntityId& entity_id) noexcept {
  entity_id_ = entity_id;
}

Component::Component() noexcept : entity_id_(0) {
}

std::size_t Component::GetComponentsTypesCount() {
  return components_types_counter_;
}

}  // namespace component
}  // namespace ecs