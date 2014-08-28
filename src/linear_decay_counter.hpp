#ifndef LINEAR_DECAY_COUNTER_HPP_CEC2EE4C_828C_4C54_A3DD_D1FAA9A074A7_
#define LINEAR_DECAY_COUNTER_HPP_CEC2EE4C_828C_4C54_A3DD_D1FAA9A074A7_

#include <stdint.h>
#include <pficommon/data/unordered_map.h>

#include "counter.hpp"

namespace counter {

/*
 * Score of a word w which observed in [t_1...t_n] at time `now` is defined as:
 * \sum_{t \in [t_1..t_n]} max(0, decay_ratio * (now - t))
 */
template <typename T>
class LinearDecayCounter : public Counter<T> {
 public:
  typedef uint64_t IdType;
  typedef uint64_t TimeType;

  explicit LinearDecayCounter(double decay_ratio);

  void Add(const T& id);

  double Get(const T& id) const;

 private:
  double CalcPenalty(TimeType time) const;

  struct Element {
    double score;
    TimeType time;
  };

  typedef pfi::data::unordered_map<IdType, Element> ScoreMap;
  
  ScoreMap scores_;
  TimeType time_;
  double decay_ratio_;
};

template <typename T>
LinearDecayCounter<T>::LinearDecayCounter(double decay_ratio)
    : decay_ratio_(decay_ratio) {
}

template <typename T>
void LinearDecayCounter<T>::Add(const T& id) {
  ++time_;
  Element& e = scores_[id];
  e.score = GetScore(id) + 1.0;
  e.time = time_;
}

template <typename T>
double LinearDecayCounter<T>::Get(const T& id) const {
  typename ScoreMap::const_iterator it = scores_.find(id);
  if (it == scores_.end()) {
    return 0.0;
  } else {
    const Element& e = it->second;
    return std::max(0.0, e.score - CalcPenalty(e.time));
  }
}

template <typename T>
double LinearDecayCounter<T>::CalcPenalty(TimeType time) const {
  return decay_ratio_ * (time_ - time);
}

}  // namespace counter

#endif  // LINEAR_DECAY_COUNTER_HPP_CEC2EE4C_828C_4C54_A3DD_D1FAA9A074A7_
