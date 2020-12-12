#include "systems_manager.hpp"

#include "gtest/gtest.h"

class SystemsManagerTest : public ::testing::Test {
 protected:
  void SetUp() override;
  void TearDown() override;
};

TEST_F(SystemsManagerTest, AddSystem) {
}

TEST_F(SystemsManagerTest, AddDependency) {
}

TEST_F(SystemsManagerTest, FindsTopoligicalOrder) {
}

TEST_F(SystemsManagerTest, CallingSystemsMethodsInTopologicalOrder) {
}

TEST_F(SystemsManagerTest, ThrowsExceptionIfSystemsDependencyHasCycle) {
}