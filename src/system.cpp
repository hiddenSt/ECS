#include "system.hpp"

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

std::size_t ecs::System::GetSystemTypesCount() {
  return systems_types_counter_;
}