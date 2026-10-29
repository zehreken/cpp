#pragma once

#include <cstddef>
#include <utility>

// Improved Vector implementation
template <typename T> class ImpVector {
  public:
    explicit ImpVector(size_t capacity) {
        size_ = 0;
        capacity_ = capacity > 0 ? capacity : 1;
        data_ = std::make_unique<T[]>(capacity_); //
        // data_ = std::unique_ptr<T[]>(new T[capacity_]); // also works
    }

    ImpVector(const ImpVector& other) {
        size_ = other.size();
        capacity_ = other.capacity();
        data_ = std::make_unique<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
    } // copy ctor

    ImpVector& operator=(const ImpVector& other) {
        if (this == &other)
            return *this;

        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(other.capacity_);
        for (size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other[i];
        }
        data_ = std::move(new_data);
        size_ = other.size();
        capacity_ = other.capacity();

        return *this;
    } // copy assign

    ImpVector(ImpVector&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_),
          capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    } // move ctor

    ImpVector& operator=(ImpVector&& other) noexcept {
        if (this == &other)
            return *this;

        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }
    // move assign

    T& operator[](size_t i) const { return data_[i]; }

    void reserve(size_t n) {
        if (n <= capacity_)
            return;

        capacity_ = n;
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        data_ = std::move(new_data);
    }

    void push_back(const T& e) {
        if (size_ + 1 > capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }
        data_[size_++] = e;
    }
    void emplace_back(const T& e) {}

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

  private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
};