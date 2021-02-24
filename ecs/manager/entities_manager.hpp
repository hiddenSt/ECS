#ifndef ECS_INCLUDE_ENTITIES_MANAGER_HPP_
#define ECS_INCLUDE_ENTITIES_MANAGER_HPP_

#include <ecs/entity/entities_id_container.hpp>

namespace ecs {
namespace manager {

class EntitiesManager {
 public:
  static EntitiesManager& Instance();
  static EntitiesManager& Initialize(unsigned char* memory_ptr,
                                     entity::EntitiesIdContainer& entities_id_container);
  static void Destroy();

  EntityId CreateEntity();
  void RemoveEntity(const EntityId& entity_id);

 private:
  EntitiesManager(entity::EntitiesIdContainer& entities_id_container);

  entity::EntitiesIdContainer& entities_id_container_;
  std::size_t entities_counter_;
  static EntitiesManager* instance_;
};

}  // namespace manager
}  // namespace ecs

#endif  // ECS_INCLUDE_ENTITIES_MANAGER_HPP_
