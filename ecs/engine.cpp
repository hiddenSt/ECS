#include <allocators/stack_allocator/stack_allocator.hpp>
#include <ecs/engine.hpp>
#include <stdexcept>

namespace ecs {

ecs::Engine* ecs::Engine::instance_ = nullptr;

Engine& Engine::Instance() {
  if (instance_ == nullptr) {
    throw std::logic_error("Engine is not initialized.");
  }

  return *instance_;
}

void Engine::Initialize(unsigned char* memory_arena, const uint64_t& memory_size_bytes,
                        const std::size_t& max_components_per_type) {
  std::size_t components_types_count = component::Component::GetComponentsTypesCount();
  instance_ =
      new Engine(memory_arena, memory_size_bytes, max_components_per_type, components_types_count);
}

Engine::Engine(unsigned char* memory_arena, const uint64_t& memory_size_bytes,
               const std::size_t& max_components_per_type, const std::size_t& component_types_count)
    : memory_size_bytes_(memory_size_bytes),
      max_components_per_type_(max_components_per_type),
      allocator_(memory_arena, memory_size_bytes),
      pool_allocators_(component_types_count, nullptr),
      components_manager_memory_ptr_(nullptr),
      systems_manager_memory_ptr_(nullptr),
      entities_manager_memory_ptr_(nullptr),
      set_entities_id_container_(nullptr),
      systems_count_(0) {
  systems_manager_memory_ptr_ =
      static_cast<unsigned char*>(allocator_.Allocate(sizeof(manager::SystemsManager), 8));
  manager::SystemsManager::Initialize(systems_manager_memory_ptr_);
  components_manager_memory_ptr_ =
      static_cast<unsigned char*>(allocator_.Allocate(sizeof(manager::ComponentsManager), 8));
  entities_manager_memory_ptr_ =
      static_cast<unsigned char*>(allocator_.Allocate(sizeof(manager::EntitiesManager), 8));
  manager::ComponentsManager::Initialize(components_manager_memory_ptr_,
                                         component::Component::GetComponentsTypesCount());
  set_entities_id_container_ = new util::SetEntitiesIdContainer();
  manager::EntitiesManager::Initialize(entities_manager_memory_ptr_, *set_entities_id_container_);
}

EntityId Engine::CreateEntity() {
  return manager::EntitiesManager::Instance().CreateEntity();
}

void Engine::MakeTic() {
  manager::SystemsManager::Instance().PreUpdate();
  manager::SystemsManager::Instance().Update();
  manager::SystemsManager::Instance().PostUpdate();
}

void Engine::SetUp() {
  manager::SystemsManager::Instance().SetUp();
}

void Engine::ShutDown() {
  manager::SystemsManager::Destroy();
  allocator_.Free();
  manager::ComponentsManager::Destroy();
  allocator_.Free();
  manager::EntitiesManager::Destroy();
  allocator_.Free();
  for (std::size_t i = 0; i <= pool_allocators_.size(); ++i) {
    if (pool_allocators_[i] != nullptr)
      allocator_.Free();
  }
  instance_ = nullptr;
}

void Engine::DestroyEntity(const EntityId& entity_id) {
  manager::ComponentsManager::Instance().RemoveEntitiesComponents(entity_id);
  manager::EntitiesManager::Instance().RemoveEntity(entity_id);
}

void Engine::SetSystemsDependency(system::System* system_dependent, system::System* depends_on) {
  manager::SystemsManager::Instance().AddDependency(system_dependent, depends_on);
}
}  // namespace ecs