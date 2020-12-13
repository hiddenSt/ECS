#ifndef ECS_INCLUDE_SYSTEM_HPP_
#define ECS_INCLUDE_SYSTEM_HPP_

#include "types.hpp"

namespace ecs {

class System {
 public:
  static std::size_t GetSystemTypesCount();

  template <typename ConcreteSystem>
  static SystemTypeId SetSystemTypeId();

  virtual SystemTypeId GetSystemTypeId() const noexcept = 0;

  virtual void SetUp() {}
  virtual void ShutDown() {}
  virtual void Update() {}
  virtual void PreUpdate() {}
  virtual void PostUpdate() {}


  static std::size_t systems_types_counter_;
};

template <typename ConcreteSystem>
ecs::SystemTypeId ecs::System::SetSystemTypeId() {
  static SystemTypeId new_system_type_id = ++systems_types_counter_;
  return new_system_type_id;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_HPP_
