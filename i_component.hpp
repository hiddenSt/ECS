#ifndef ECS__I_COMPONENT_HPP_
#define ECS__I_COMPONENT_HPP_

#include "types.hpp"

namespace ecs {

class IComponent {
 public:
  explicit IComponent(const EntityId& entity_id, bool enabled) noexcept;
  virtual ~IComponent();

  EntityId GetEntityId() const noexcept;
  void Activate() noexcept;
  void Deactivate() noexcept;
  bool IsActive() const noexcept;
  virtual ComponentTypeId GetComponentTypeId() const noexcept = 0;

 private:
  EntityId entity_id_;
  bool enabled_;
};

}  // namespace ecs

#endif  // ECS__I_COMPONENT_HPP_
