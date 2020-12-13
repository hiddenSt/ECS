#ifndef ECS_INCLUDE_ENTITY_MANAGER_HPP_
#define ECS_INCLUDE_ENTITY_MANAGER_HPP_

#include "entitys_id_container.hpp"

namespace ecs {

class EntityManager {
 public:
  static EntityManager& Instance();
  static EntityManager& Create(EntitysIdContainer& entitys_id_container);

  EntityId CreateEntity();
  void RemoveEntity(const EntityId& entity_id);

 private:
  EntityManager(EntitysIdContainer& entitys_id_container);

  EntitysIdContainer& entitys_id_container_;
  std::size_t entitys_counter_;

  static EntityManager* instance_;
};

}  // namespace ecs

#endif  // ECS_INCLUDE_ENTITY_MANAGER_HPP_
