#ifndef LOSSY_COUNTER_HPP_AB016FF0_4A63_414C_8F4B_8CFDB6F46098_
#define LOSSY_COUNTER_HPP_AB016FF0_4A63_414C_8F4B_8CFDB6F46098_

#include "simple_counter.hpp"

namespace counter {

template <typename T>
class LossyCounter : public Counter<T> {
 public:
  LossyCounter(double epsilon)
      : epsilon_(epsilon),
        bucket_size_(1.0 / epsilon),
        bucket_id_(1),
        insert_count_(0) {
  }

  void Add(const T& key) {
    insert_count_ += 1;
    if (data_.count(key)) {
      data_[key].count += 1;
    } else {
      data_[key].count = 1;
      data_[key].id = bucket_id_ - 1;
    }

    if (insert_count_ % bucket_size_ == 0) {
      Trim();
      bucket_id_ += 1;
    }
  }

  double Get(const T& key) const {
    typename map_type::const_iterator it = data_.find(key);
    if (it == data_.end()) {
      return 0;
    } else {
      return it->second.count;
    }
  }

 private:
  void Trim() {
    for (typename map_type::iterator it = data_.begin();
         it != data_.end(); ) {
      if (it->second.count <= bucket_id_ - it->second.id) {
        it = data_.erase(it);
      } else {
        ++it;
      }
    }
  }

  struct bucket_entry {
    int count;
    int id;
  };

  double epsilon_;
  size_t bucket_size_;
  int bucket_id_;
  int insert_count_;
  typedef pfi::data::unordered_map<T, bucket_entry> map_type;
  map_type data_;
};

}  // namespace counter

#endif // LOSSY_COUNTER_HPP_AB016FF0_4A63_414C_8F4B_8CFDB6F46098_
