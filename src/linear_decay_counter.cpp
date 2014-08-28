#include "linear_decay_counter.hpp"

namespace counter {

LinearDecayCounter::LinearDecayCounter(double decay_ratio)
    : decay_ratio_(decay_ratio) {
}

void LinearDecayCounter::Add(IdType id) {
  ++time_;
  Element& e = scores_[id];
  e.score = GetScore(id) + 1.0;
  e.time = time_;
}

double LinearDecayCounter::GetScore(IdType id) const {
  ScoreMap::const_iterator it = scores_.find(id);
  if (it == scores_.end()) {
    return 0.0;
  } else {
    const Element& e = it->second;
    return std::max(0.0, e.score - CalcPenalty(e.time));
  }
}

double LinearDecayCounter::CalcPenalty(TimeType time) const {
  return decay_ratio_ * (time_ - time);
}

}  // namespace counter
