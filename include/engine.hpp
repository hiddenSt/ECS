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
#include "utility/map_look_up_table.hpp"
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
  T* GetComponent(const EntityId& entity_id);

  template <typename T, typename... Args>
  T* AddSystem(Args&&... args);
  void SetSystemsDependency(System* system_dependent, System* depends_on);

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
  std::size_t systems_count_;
  uint64_t memory_size_bytes_;
  std::size_t max_components_per_type_;
  std::vector<allocators::PoolAllocator*> pool_allocators_;
  unsigned char* components_manager_memory_ptr_;
  unsigned char* entities_manager_memory_ptr_;
  unsigned char* systems_manager_memory_ptr_;
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
T* Engine::GetComponent(const EntityId& entity_id) {
  if (pool_allocators_[T::StaticGetComponentTypeId()] == nullptr) {
    AddComponentTypeContainer<T>();
  }
  return ComponentsManager::Instance().GetComponent<T>(entity_id);
}

template <typename T>
void Engine::AddComponentTypeContainer() {
  uint64_t memory_size_bytes = sizeof(T) * max_components_per_type_;
  auto* allocated_memory = static_cast<unsigned char*>(allocator_.Allocate(memory_size_bytes, 8));
  if (allocated_memory == nullptr) {
    throw std::bad_alloc();
  }

  auto* map_look_up_table = new util::MapLookUpTable();

  auto* pool_allocator =
      new allocators::PoolAllocator(allocated_memory, memory_size_bytes, sizeof(T));
  pool_allocators_[T::StaticGetComponentTypeId()] = pool_allocator;
  auto* components_container =
      new ComponentTypeContainer<T, allocators::PoolAllocator>(*pool_allocator, *map_look_up_table);
  ComponentsManager::Instance().AddComponentsContainer(components_container);
}

template <typename T, typename... Args>
T* ecs::Engine::AddSystem(Args&&... args) {
  auto* allocated_memory = allocator_.Allocate(sizeof(T), 8);
  if (allocated_memory == nullptr) {
    throw std::bad_alloc();
  }
  ++systems_count_;
  T* system = new (allocated_memory) T(std::forward<Args>(args)...);
  SystemsManager::Instance().AddSystem(system);
  return system;
}

}  // namespace ecs
#endif  // ECS_INCLUDE_ENGINE_HPP_
