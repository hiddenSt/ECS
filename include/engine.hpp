#ifndef ECS_INCLUDE_ENGINE_HPP_
#define ECS_INCLUDE_ENGINE_HPP_

#include <vector>

#include "component_type.hpp"
#include "components_manager.hpp"
#include "entities_manager.hpp"
#include "pool_allocator.hpp"
#include "stack_allocator.hpp"
#include "system_type.hpp"
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
  Engine(unsigned char* memory_arena, const uint64_t& memory_size_bytes,
         const std::size_t& max_components_per_type);

  template <typename T>
  void AddComponentTypeContainer();

  static Engine* instance_;
  uint64_t memory_size_bytes_;
  std::size_t max_components_per_type_;
  std::vector<allocators::PoolAllocator*> pool_allocators_;
  std::vector<unsigned char*> allocated_memory_pointers_;
  allocators::StackAllocator allocator_;
};

template <typename T, typename... Args>
T* ecs::Engine::AddComponent(const ecs::EntityId& entity_id, Args&&... args) {
  T* component =
      ComponentsManager::Instance().AddComponent<T>(entity_id, std::forward<Args>(args)...);
  if (component == nullptr) {
    AddComponent<T>();
  }
}

template <typename T>
void Engine::RemoveComponent(const EntityId& entity_id) {
  ComponentsManager::Instance().RemoveComponent<T>(entity_id);
}

template <typename T>
T Engine::GetComponent(const EntityId& entity_id) {
  return ComponentsManager::Instance().GetComponent<T>(entity_id);
}

template <typename T>
void Engine::AddComponentTypeContainer() {
  void* allocated_memory = allocator_.Allocate(sizeof(T)*max_components_per_type_, 1);
  allocated_memory_pointers_.push_back(static_cast<unsigned char*>(allocated_memory));
  auto* pool_allocator = new allocators::PoolAllocator();
}

void Engine::DestroyEntity(const EntityId& entity_id) {
}

}  // namespace ecs
#endif  // ECS_INCLUDE_ENGINE_HPP_
