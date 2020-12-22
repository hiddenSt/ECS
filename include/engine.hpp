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
#include "utility/set_entities_id_container.hpp"

namespace ecs {

class Engine {
 public:
  static void Initialize(unsigned char* memory_arena, const uint64_t& memory_size_bytes,
                         const std::size_t& max_components_per_type);
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
         const std::size_t& max_components_per_type, const std::size_t& component_types_count);

  template <typename T>
  void AddComponentTypeContainer();

  static Engine* instance_;
  uint64_t memory_size_bytes_;
  std::size_t max_components_per_type_;
  std::vector<allocators::PoolAllocator*> pool_allocators_;
  unsigned char* components_manager_memory_ptr_;
  unsigned char* entities_manager_memory_ptr_;
  unsigned char* systems_manager_memory_ptr_;
  std::vector<unsigned char*> allocated_memory_pointers_;
  allocators::StackAllocator allocator_;
  util::SetEntitiesIdContainer* set_entities_id_container_;
};

template <typename T, typename... Args>
T* ecs::Engine::AddComponent(const ecs::EntityId& entity_id, Args&&... args) {
  if (pool_allocators_[T::StaticGetComponentTypeId()] == nullptr) {
    AddComponentTypeContainer<T>();
  }
  T* component =
      ComponentsManager::Instance().AddComponent<T>(entity_id, std::forward<Args>(args)...);
  return component;
}

template <typename T>
void Engine::RemoveComponent(const EntityId& entity_id) {
  ComponentsManager::Instance().RemoveComponent<T>(entity_id);
}

template <typename T>
T Engine::GetComponent(const EntityId& entity_id) {
  if (pool_allocators_[T::StaticGetComponentTypeId()] == nullptr) {
    AddComponentTypeContainer<T>();
  }
  return ComponentsManager::Instance().GetComponent<T>(entity_id);
}

template <typename T>
void Engine::AddComponentTypeContainer() {
  uint64_t memory_size_bytes = sizeof(T) * max_components_per_type_;
  auto* allocated_memory =
      static_cast<unsigned char*>(allocator_.Allocate(memory_size_bytes, sizeof(T)));

  if (allocated_memory == nullptr) {
    throw std::bad_alloc();
  }

  allocated_memory_pointers_.push_back(allocated_memory);
  auto* pool_allocator =
      new allocators::PoolAllocator(allocated_memory, memory_size_bytes, sizeof(T));
  pool_allocators_[T::StaticGetComponentTypeId()] = pool_allocator;
}



}  // namespace ecs
#endif  // ECS_INCLUDE_ENGINE_HPP_
