#ifndef ECS_INCLUDE_ENGINE_HPP_
#define ECS_INCLUDE_ENGINE_HPP_

#include "components_manager.hpp"
#include "entities_manager.hpp"
#include "systems_manager.hpp"

namespace ecs {

class Engine {
 public:
  static void Initialize(std::size_t max_components_per_type);
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
  Engine();

  static Engine* instance_;
  uint64_t memory_size_bytes_;
};

template <typename T, typename... Args>
T* ecs::Engine::AddComponent(const ecs::EntityId& entity_id, Args&&... args) {
  ComponentsManager::Instance().AddComponent<T>(entity_id, std::forward<Args>(args)...);
}

template <typename T>
void Engine::RemoveComponent(const EntityId& entity_id) {
  ComponentsManager::Instance().RemoveComponent<T>(entity_id);
}

template <typename T>
T Engine::GetComponent(const EntityId& entity_id) {
  return ComponentsManager::Instance().GetComponent<T>(entity_id);
}

void Engine::DestroyEntity(const EntityId& entity_id) {
}

}  // namespace ecs
#endif  // ECS_INCLUDE_ENGINE_HPP_
