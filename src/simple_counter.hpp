#ifndef SIMPLE_COUNTER_HPP_E67D6823_0CCE_466A_8BA3_2D1BA03F2884_
#define SIMPLE_COUNTER_HPP_E67D6823_0CCE_466A_8BA3_2D1BA03F2884_

#include <pficommon/data/unordered_map.h>
#include "counter.hpp"

namespace counter {

template <typename T>
class SimpleCounter : public Counter<T> {
 public:
  void Add(const T& key) {
    data_[key] += 1;
  }

  double Get(const T& key) const {
    typename map_type::const_iterator it = data_.find(key);
    if (it == data_.end()) {
      return 0;
    } else {
      return it->second;
    }
  }

 private:
  typedef pfi::data::unordered_map<T, int> map_type;
  map_type data_;
};

}  // namespace counter

#endif // SIMPLE_COUNTER_HPP_E67D6823_0CCE_466A_8BA3_2D1BA03F2884_
