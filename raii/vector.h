#pragma once

#include <cstddef>
#include <utility>

template <typename T> class Vector {
  public:
    explicit Vector(size_t capacity) {
        size_ = 0;
        capacity_ = capacity > 0 ? capacity_ : 1;
        data_ = new T[capacity_];
    }
    Vector(const Vector& other) {}              // copy ctor
    Vector& operator=(const Vector& other);     // copy assign
    Vector(Vector&& other) noexcept;            // move ctor
    Vector& operator=(Vector&& other) noexcept; // move assign
    ~Vector() { delete[] data_; }

    void reserve(size_t n) {
        if (n <= capacity_)
            return;

        capacity_ = n;
        T* new_data = new T[capacity_];
        // This does not work for strings, write a short blog post
        // std::memcpy(new_data, data_, size_ * sizeof(T));
        // Copy element by element
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
    }
    void push_back(T& e) {
        if (size_ + 1 > capacity_) {
            reserve(capacity_ * 2);
        }
        data_[size_++] = e;
    }
    void emplace_back(T& e) {}
    size_t size() { return size_; }
    size_t capacity() { return capacity_; }

  private:
    T* data_;
    size_t size_;
    size_t capacity_;
};

template <typename T> class Vector0 {
  public:
  private:
};
