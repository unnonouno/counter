#include <gtest/gtest.h>

#include "lossy_counter.hpp"

namespace counter {

TEST(LossyCounter, trivial) {
  LossyCounter<int> c(0.005);
  std::vector<int> values;
  for (int i = 1; i <= 100; ++i) {
    for (int j = 0; j < 100 / i; ++j)
      values.push_back(i);
  }

  for (int i = 0; i < 1000; ++i) {
    int ind = rand() % values.size();
    c.Add(values[ind]);
  }

  for (int i = 1; i <= 100; ++i) {
    if (c.Get(i) > 0)
      std::cout << i << ": " << c.Get(i) << std::endl;
  }
}

}  // namespace counter
