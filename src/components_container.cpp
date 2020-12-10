#include "components_container.hpp"

ecs::ComponentsContainer::ComponentsContainer(const ComponentTypeId& component_type_id) noexcept
    : COMPONENT_TYPE_ID_(component_type_id) {
}

const ecs::ComponentTypeId ecs::ComponentsContainer::GetComponentTypeId() const noexcept {
  return COMPONENT_TYPE_ID_;
}
