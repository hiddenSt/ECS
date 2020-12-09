#ifndef ECS_INCLUDE_COMPONENT_HPP_
#define ECS_INCLUDE_COMPONENT_HPP_

#include <cstdint>

namespace ecs {

class Component {
 public:
  explicit Component() noexcept;

  void SetEntityId(const std::size_t& entity_id) noexcept;
  std::size_t GetEntityId() const noexcept;
  virtual const std::size_t GetComponentTypeId() const noexcept = 0;

  static const std::size_t GetComponentsTypesCount();
  template <typename T>
  static const std::size_t SetComponentTypeId();

 private:
  static std::size_t components_types_counter;

  std::size_t entity_id_;
};

template <typename T>
const std::size_t ecs::Component::SetComponentTypeId() {
  static std::size_t new_type_id = ++components_types_counter;
  return new_type_id;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_COMPONENT_HPP_
