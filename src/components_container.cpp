#include "components_container.hpp"

ecs::ComponentsContainer::ComponentsContainer(const ComponentTypeId& component_type_id) noexcept
    : kComponentTypeId_(component_type_id) {
}

ecs::ComponentTypeId ecs::ComponentsContainer::GetComponentTypeId() const noexcept {
  return kComponentTypeId_;
}
