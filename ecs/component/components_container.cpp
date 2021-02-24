#include <ecs/component/components_container.hpp>

namespace ecs {
namespace component {

ComponentsContainer::ComponentsContainer(const ComponentTypeId& component_type_id) noexcept
    : kComponentTypeId_(component_type_id) {
}

ComponentTypeId ComponentsContainer::GetComponentTypeId() const noexcept {
  return kComponentTypeId_;
}


}  // namespace component
}  // namespace ecs

