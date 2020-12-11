#ifndef ECS_INCLUDE_ENTITY_MANAGER_HPP_
#define ECS_INCLUDE_ENTITY_MANAGER_HPP_

namespace ecs {

class EntityManager {
 public:
  static EntityManager& Instance();
 private:
  EntityManager();

  static EntityManager* instance_;
  
};

EntityManager* EntityManager::instance_ = nullptr;
}  // namespace ecs

#endif  // ECS_INCLUDE_ENTITY_MANAGER_HPP_
