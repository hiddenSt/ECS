#ifndef ECS_INCLUDE_SYSTEMS_MANAGER_HPP_
#define ECS_INCLUDE_SYSTEMS_MANAGER_HPP_

#include <stdexcept>
#include <vector>

#include "system.hpp"

namespace ecs {

class SystemsManager {
 public:
  static SystemsManager& Instance();

  static void Initialize();
  static void Destroy();

  void AddSystem(System* system);
  void AddDependency(System* dependent, System* independent);
  void SetUp();
  void PreUpdate();
  void Update();
  void PostUpdate();

 private:
  explicit SystemsManager(const std::size_t& number_of_system_types);
  explicit SystemsManager(const SystemsManager& other) = delete;

  void FindTopologicalOrder();
  void Dfs(std::vector<char>& color, std::size_t& source);

  static SystemsManager* instance_;

  const std::size_t kNumberOfSystemTypes;

  std::vector<std::vector<size_t>> dependency_graph_;
  std::vector<System*> systems_;
  std::vector<System*> systems_topological_order_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEMS_MANAGER_HPP_
