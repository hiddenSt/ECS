#ifndef ECS_INCLUDE_SYSTEM_MANAGER_HPP_
#define ECS_INCLUDE_SYSTEM_MANAGER_HPP_

#include <vector>

#include "system.hpp"

namespace ecs {

class SystemManager {
 public:
  void Initialize();
  void AddSystem(System* system);
  void PreUpdate();
  void Update();
  void PostUpdate();
  void AddDependency();

 protected:
 private:
  std::vector<System*> systems_topological_order_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_MANAGER_HPP_
