#ifndef ECS_INCLUDE_SYSTEM_TYPE_HPP_
#define ECS_INCLUDE_SYSTEM_TYPE_HPP_

#include "system.hpp"
#include "types.hpp"

namespace ecs {

template <typename T>
class SystemType : public System {
 public:
  static SystemTypeId StaticGetSystemTypeId();

  SystemTypeId GetSystemTypeId() const noexcept override;

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

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_TYPE_HPP_
