#ifndef ECS_INCLUDE_SYSTEM_HPP_
#define ECS_INCLUDE_SYSTEM_HPP_

#include "types.hpp"

namespace ecs {

class System {
 public:
  template <typename ConcreteSystem>
  static SystemTypeId SetSystemTypeId();
  static std::size_t GetSystemTypesCount();

  virtual SystemTypeId GetSystemTypeId() const noexcept = 0;

  virtual void SetUp();
  virtual void ShutDown();
  virtual void Update();
  virtual void PreUpdate();
  virtual void PostUpdate();

 private:
  static std::size_t systems_types_counter_;
};

std::size_t System::systems_types_counter_ = 0;

template <typename ConcreteSystem>
ecs::SystemTypeId ecs::System::SetSystemTypeId() {
  static SystemTypeId new_system_type_id = ++systems_types_counter_;
  return new_system_type_id;
}

void System::SetUp() {
}

void System::ShutDown() {
}

void System::Update() {
}

void System::PreUpdate() {
}

void System::PostUpdate() {
}

std::size_t System::GetSystemTypesCount() {
  return systems_types_counter_;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_HPP_
