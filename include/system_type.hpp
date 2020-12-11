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
  static const SystemTypeId kSystemTypeId;
};

template <typename T>
const SystemTypeId SystemType<T>::kSystemTypeId = System::SetSystemTypeId<T>();

template <typename T>
SystemTypeId SystemType<T>::StaticGetSystemTypeId() {
  return kSystemTypeId;
}

template <typename T>
SystemTypeId SystemType<T>::GetSystemTypeId() const noexcept {
  return kSystemTypeId;
}

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_TYPE_HPP_
