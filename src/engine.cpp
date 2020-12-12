#include "engine.hpp"

#include <stdexcept>

ecs::Engine& ecs::Engine::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error("Engine is not initialized.");
  }

  return *instance_;
}