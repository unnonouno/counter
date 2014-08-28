#include <gtest/gtest.h>

#include "decay_counter.hpp"

namespace counter {

TEST(DecayCounter, trivial) {
  DecayCounter<int> c(0.9);
  c.Add(1);
  EXPECT_EQ(1.0, c.Get(1));
}

}  // namespace counter
