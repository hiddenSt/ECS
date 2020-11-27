#ifndef ECS__I_COMPONENT_HPP_
#define ECS__I_COMPONENT_HPP_

#include <cstddef>

namespace ecs {

class IComponent {
 public:
  using EntityId = std::size_t;

  explicit IComponent(const EntityId& entity_id, bool enabled) noexcept;
  virtual ~IComponent();

  EntityId GetEntityId() const noexcept;
  void Activate() noexcept;
  void Deactivate() noexcept;
  bool IsActive() const noexcept;
  virtual std::size_t GetComponentTypeId() const noexcept = 0;

 private:
  EntityId entity_id_;
  bool enabled_;
};

}  // namespace ecs

#endif  // ECS__I_COMPONENT_HPP_
