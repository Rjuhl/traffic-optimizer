#include <gtest/gtest.h>
#include "road.h"
#include "pos.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  Road road = Road(Pos(1, 1), Pos(1, 1), nullptr);
  Pos expected = Pos(1, 1);
  Pos result = road.getStart();

  EXPECT_EQ(expected.x, result.x);
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}