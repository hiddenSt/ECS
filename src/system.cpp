#include "system.hpp"

// Sets base value for system type identifier.
std::size_t ecs::System::systems_types_counter_ = 0;

std::size_t ecs::System::GetSystemTypesCount() {
  return systems_types_counter_;
}

void ecs::System::SetUp() {
}

void ecs::System::ShutDown() {
}

void ecs::System::Update() {
}

void ecs::System::PreUpdate() {
}

void ecs::System::PostUpdate() {
}