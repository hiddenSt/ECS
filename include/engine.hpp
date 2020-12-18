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
  void SetUp();
  void ShutDown();

 private:
  Engine() = default;

  static Engine* instance_;
  ComponentsManager& components_manager_;
  EntityManager& entity_manager_;
  SystemsManager& system_manager_;
};

template <typename T, typename... Args>
T* ecs::Engine::AddComponent(const ecs::EntityId& entity_id, Args&&... args) {
  components_manager_.AddComponent<T>(entity_id, std::forward<Args>(args)...);
}

template <typename T>
void Engine::RemoveComponent(const EntityId& entity_id) {
  components_manager_.RemoveComponent<T>(entity_id);
}

template <typename T>
T Engine::GetComponent(const EntityId& entity_id) {
  return components_manager_.GetComponent<T>(entity_id)>();
}

}  // namespace ecs
#endif  // ECS_INCLUDE_ENGINE_HPP_
