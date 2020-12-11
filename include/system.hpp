#ifndef ECS_INCLUDE_SYSTEM_HPP_
#define ECS_INCLUDE_SYSTEM_HPP_

namespace ecs {

class System {
 public:
  virtual void SetUp();
  virtual void TearDown();
  virtual void Update();
  virtual void PreUpdate();
  virtual void PostUpdate();
  virtual void GetSystemTypeId();
};

}  // namespace ecs

#endif  // ECS_INCLUDE_SYSTEM_HPP_
