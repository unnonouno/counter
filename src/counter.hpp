#ifndef COUNTER_HPP_276EA385_362A_4FC0_8E76_84E4D4B723E9_
#define COUNTER_HPP_276EA385_362A_4FC0_8E76_84E4D4B723E9_

#include <stdint.h>

namespace counter {

template <typename T>
class Counter {
 public:
  virtual ~Counter() {}

  virtual void Add(const T& id) = 0;
  virtual double Get(const T& id) const = 0;
};

}  // namespace count

#endif  // COUNTER_HPP_276EA385_362A_4FC0_8E76_84E4D4B723E9_
