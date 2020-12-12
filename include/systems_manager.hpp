#ifndef ECS_INCLUDE_SYSTEMS_MANAGER_HPP_
#define ECS_INCLUDE_SYSTEMS_MANAGER_HPP_

#include <vector>

#include "system.hpp"

namespace ecs {

class SystemsManager {
 public:
  static SystemsManager& Instance();

  void Initialize();

  void AddSystem(System* system);
  void PreUpdate();
  void Update();
  void PostUpdate();
  void AddDependency(System* dependent, System* independent);

 private:
  explicit SystemsManager();
  explicit SystemsManager(const SystemsManager& other) = delete;

  void Dfs(std::vector<char> color, std::size_t source);
  void FindTopologicalOrder();

  const std::size_t kNumberOfSystemTypes;

  static SystemsManager* instance_;

  std::vector<std::vector<size_t>> dependency_graph_;
  std::vector<System*> systems_;
  std::vector<System*> systems_topological_order_;
};

SystemsManager* SystemsManager::instance_ = nullptr;

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEMS_MANAGER_HPP_
