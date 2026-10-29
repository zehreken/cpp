#pragma once

#include <cstddef>
#include <utility>

template <typename T> class Vector {
  public:
    explicit Vector(size_t capacity) {
        size_ = 0;
        capacity_ = capacity > 0 ? capacity : 1;
        data_ = new T[capacity_];
    }

    Vector(const Vector& other) {
        size_ = other.size();
        capacity_ = other.capacity();
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
    } // copy ctor

    Vector& operator=(const Vector& other) {
        if (this == &other)
            return *this;

        T* new_data = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size();
        capacity_ = other.capacity();

        return *this;
    } // copy assign

    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    } // move ctor

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other)
            return *this;

        delete[] data_;
        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }
    // move assign

    ~Vector() { delete[] data_; }

    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

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
    T* data_;
    size_t size_;
    size_t capacity_;
};

template <typename T> class Vector0 {
  public:
  private:
};
