#ifndef ECS_INCLUDE_SYSTEMS_MANAGER_HPP_
#define ECS_INCLUDE_SYSTEMS_MANAGER_HPP_

#include <ecs/system/system.hpp>
#include <stdexcept>
#include <vector>

namespace ecs {
namespace manager {

class SystemsManager {
 public:
  static SystemsManager& Instance();
  static void Initialize(unsigned char* memory_ptr);
  static void Destroy();

  void AddSystem(system::System* system);
  void AddDependency(system::System* dependent, system::System* independent);
  void SetUp();
  void PreUpdate();
  void Update();
  void PostUpdate();

  explicit SystemsManager(const SystemsManager& other) = delete;
  explicit SystemsManager(SystemsManager&& other) = delete;
  SystemsManager& operator=(const SystemsManager& other) = delete;
  SystemsManager& operator=(SystemsManager&& other) = delete;

 private:
  const std::size_t kNumberOfSystemTypes_;

  explicit SystemsManager(const std::size_t& number_of_system_types);
  ~SystemsManager() = default;

  void FindTopologicalOrder();
  void Dfs(std::vector<char>& color, std::size_t& source);

  static SystemsManager* instance_;
  std::vector<std::vector<size_t>> dependency_graph_;
  std::vector<system::System*> systems_;
  std::vector<system::System*> systems_topological_order_;
};

}  // namespace manager
}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEMS_MANAGER_HPP_
