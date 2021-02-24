#ifndef ECS_INCLUDE_SYSTEM_TYPE_HPP_
#define ECS_INCLUDE_SYSTEM_TYPE_HPP_

#include <ecs/system/system.hpp>
#include <ecs/types.hpp>

namespace ecs {
namespace system {

template <typename T>
class SystemType : public System {
 public:
  SystemTypeId GetSystemTypeId() const noexcept override;
  static SystemTypeId StaticGetSystemTypeId();

 private:
  static const SystemTypeId kSystemTypeId_;
};

template <typename T>
const SystemTypeId SystemType<T>::kSystemTypeId_ = System::SetSystemTypeId<T>();

template <typename T>
SystemTypeId SystemType<T>::StaticGetSystemTypeId() {
  return kSystemTypeId_;
}

template <typename T>
SystemTypeId SystemType<T>::GetSystemTypeId() const noexcept {
  return kSystemTypeId_;
}

}  // namespace system
}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_TYPE_HPP_
