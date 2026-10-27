#pragma once

#include <cstddef>
#include <utility>

// Improved Vector implementation
template <typename T> class ImpVector {
  public:
    explicit ImpVector(size_t capacity) {}

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

  private:
    std::unique_ptr<T> data_;
    size_t size_;
    size_t capacity_;
};