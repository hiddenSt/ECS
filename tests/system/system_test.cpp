#include <ecs/system/system_type.hpp>

#include <gtest/gtest.h>

class SystemTest : public ::testing::Test {
 protected:
  struct SystemType1 : public ecs::system::SystemType<SystemType1> {
    SystemType1() = default;
    void Update() override {
      int a;
    }
    void PreUpdate() override {
      int b;
    }

    int param1;
    int param2;
  };

  struct SystemType2 : public ecs::system::SystemType<SystemType2> {
    SystemType2() = default;
    void Update() override {
      int a;
    }
    void PreUpdate() override {
      int b;
    }

    int param1;
    double param2;
  };
};

TEST_F(SystemTest, GeneratesUniqueId) {
  auto system_1_type_id = SystemType1::StaticGetSystemTypeId();
  auto system_2_type_id = SystemType2::StaticGetSystemTypeId();
  ASSERT_NE(system_1_type_id, system_2_type_id);
}

TEST_F(SystemTest, CanAccessCorrectTypeIdThroughObject) {
  SystemType1 system_type_1;
  SystemType2 system_type_2;
  ASSERT_EQ(system_type_1.GetSystemTypeId(), SystemType1::StaticGetSystemTypeId());
  ASSERT_EQ(system_type_2.GetSystemTypeId(), SystemType2::StaticGetSystemTypeId());
}
