#ifndef ECS_INCLUDE_SYSTEM_MANAGER_HPP_
#define ECS_INCLUDE_SYSTEM_MANAGER_HPP_

#include <vector>

#include "system.hpp"

namespace ecs {

class SystemManager {
 public:
  static SystemManager& Instance();

  void Initialize();
  void AddSystem(System* system);
  void PreUpdate();
  void Update();
  void PostUpdate();
  void AddDependency();

 private:
  explicit SystemManager() = default;
  explicit SystemManager(const SystemManager& other) = delete;

  static SystemManager* instance_;

  std::vector<System*> systems_topological_order_;
};

SystemManager* SystemManager::instance_ = nullptr;

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_MANAGER_HPP_
