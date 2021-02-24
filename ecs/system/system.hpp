#ifndef ECS_INCLUDE_SYSTEM_HPP_
#define ECS_INCLUDE_SYSTEM_HPP_

#include <ecs/types.hpp>

namespace ecs {
namespace system {

class System {
 public:
  System() = default;
  virtual ~System() = default;

  explicit System(const System& other) = delete;
  explicit System(System&& other) = delete;
  System& operator=(const System& other) = delete;
  System& operator=(System&& other) = delete;

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

template <typename ConcreteSystem>
SystemTypeId System::SetSystemTypeId() {
  static SystemTypeId new_system_type_id = ++systems_types_counter_;
  return new_system_type_id;
}

}  // namespace system
}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_HPP_
