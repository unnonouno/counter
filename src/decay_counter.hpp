#ifndef DECAY_COUNTER_HPP_84650F86_0813_4885_B906_F011FD0C5367_
#define DECAY_COUNTER_HPP_84650F86_0813_4885_B906_F011FD0C5367_

#include <stdint.h>
#include <pficommon/data/unordered_map.h>

#include "counter.hpp"

namespace counter {

/*
 * Score of a word w which observed in [t_1...t_n] at time `now` is defined as:
 * \sum_{t \in [t_1..t_n]} exp(decay_ratio, now - t)
 */
template <typename T>
class DecayCounter : public Counter<T> {
 public:
  typedef uint64_t TimeType;

  explicit DecayCounter(double decay_ratio);

  void Add(const T& id);

  double Get(const T& id) const;

 private:
  double CalcDecayPenalty(TimeType time) const;

  struct Element {
    double score;
    TimeType time;
  };

  typedef pfi::data::unordered_map<T, Element> ScoreMap;
  
  ScoreMap scores_;
  TimeType time_;
  double log_decay_ratio_;
};

template <typename T>
DecayCounter<T>::DecayCounter(double decay_ratio) {
  log_decay_ratio_ = std::log(decay_ratio);
}

template <typename T>
void DecayCounter<T>::Add(const T& id) {
  ++time_;
  Element& e = scores_[id];
  e.score = Get(id) + 1.0;
  e.time = time_;
}

template <typename T>
double DecayCounter<T>::Get(const T& id) const {
  typename ScoreMap::const_iterator it = scores_.find(id);
  if (it == scores_.end()) {
    return 0.0;
  } else {
    const Element& e = it->second;
    return e.score * CalcDecayPenalty(e.time);
  }
}

template <typename T>
double DecayCounter<T>::CalcDecayPenalty(TimeType time) const {
  TimeType diff = time_ - time;
  return std::exp(log_decay_ratio_ * diff);
}

}  // namespace counter

#endif  // DECAY_COUNTER_HPP_84650F86_0813_4885_B906_F011FD0C5367_
