#include <ecs/system/system.hpp>

namespace ecs {
namespace system {

std::size_t System::systems_types_counter_ = 0;

std::size_t System::GetSystemTypesCount() {
  return systems_types_counter_;
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

}  // namespace system
}  // namespace ecs