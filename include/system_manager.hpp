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
  void AddDependency(System* dependent, System* independent);

 private:
  explicit SystemManager() = default;
  explicit SystemManager(const SystemManager& other) = delete;

  void FindTopologicalOrder();

  static SystemManager* instance_;

  std::vector<std::vector<size_t>> dependency_graph_;

  std::vector<System*> systems_topological_order_;
};

SystemManager* SystemManager::instance_ = nullptr;

void SystemManager::FindTopologicalOrder() {
}

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_MANAGER_HPP_
