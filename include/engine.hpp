#ifndef ECS_INCLUDE_ENGINE_HPP_
#define ECS_INCLUDE_ENGINE_HPP_

#include "components_manager.hpp"
#include "entity_manager.hpp"
#include "systems_manager.hpp"

namespace ecs {

class Engine {
 public:
  static void Initialize();
  static Engine& Instance();

  template <typename T, typename... Args>
  T* AddComponent(const EntityId& entity_id, Args&&... args);

  template <typename T>
  void RemoveComponent(const EntityId& entity_id);

  template <typename T>
  T GetComponent(const EntityId& entity_id);

  EntityId CreateEntity();
  void DestroyEntity(const EntityId& entity_id);
  void MakeTic();
  void ShutDown();

 private:
  Engine() = default;

  static Engine* instance_;
  ComponentsManager& components_manager_;
  EntityManager& entity_manager_;
  SystemsManager& system_manager_;
};

Engine* Engine::instance_ = nullptr;

}  // namespace ecs
#endif  // ECS_INCLUDE_ENGINE_HPP_
