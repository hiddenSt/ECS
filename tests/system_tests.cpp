#include "gtest/gtest.h"
#include "system_type.hpp"

class SystemTest : public ::testing::Test {
 protected:
  void SetUp() override {

  }

  void TearDown() override {

  }

  struct SystemType1 : public ecs::SystemType<SystemType1> {
    SystemType1() = default;
    void Update() override { int a; }
    void PreUpdate() override { int b; }

    int param1;
    int param2;
  };

  struct SystemType2 : public ecs::SystemType<SystemType2> {
    SystemType2() = default;
    void Update() override { int a; }
    void PreUpdate() override { int b; }

    int param1;
    double param2;
  };
};

TEST_F(SystemTest, GeneratesUniqueId) {
  ASSERT_NE(SystemType1::StaticGetSystemTypeId(), SystemType2::StaticGetSystemTypeId());
  ASSERT_EQ(SystemType1::StaticGetSystemTypeId(), 1);
  ASSERT_EQ(SystemType2::StaticGetSystemTypeId(), 2);
}

TEST_F(SystemTest, CanAccessRightTypeIdThroughObject) {
  SystemType1 system_type_1;
  SystemType2 system_type_2;
  ASSERT_EQ(system_type_1.GetSystemTypeId(), SystemType1::StaticGetSystemTypeId());
  ASSERT_EQ(system_type_2.GetSystemTypeId(), SystemType2::StaticGetSystemTypeId());
}
