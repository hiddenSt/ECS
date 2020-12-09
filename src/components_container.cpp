
#include "components_container.hpp"
ecs::ComponentsContainer::ComponentsContainer(const std::size_t& component_type_id) noexcept
    : COMPONENT_TYPE_ID_(component_type_id) {
}

const std::size_t ecs::ComponentsContainer::GetComponentTypeId() const noexcept {
  return COMPONENT_TYPE_ID_;
}
