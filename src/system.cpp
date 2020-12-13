#include "system.hpp"

std::size_t ecs::System::systems_types_counter_ = 0;

std::size_t ecs::System::GetSystemTypesCount() {
  return systems_types_counter_;
}
