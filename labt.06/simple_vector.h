#pragma once

#include <cstdlib>
#include <algorithm> 


template <typename T>
class SimpleVector {
public:
  SimpleVector() : data_(nullptr), size_(0), capacity_(0) {} 

  explicit SimpleVector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {
    
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = T();
    }
  }

  ~SimpleVector() { 
    delete[] data_;
  }

  T& operator[](size_t index) {
    return data_[index];
  }

  const T& operator[](size_t index) const { 
      return data_[index];
  }

  T* begin() { 
    return data_;
  }
  T* end() { 
    return data_ + size_;
  }

  const T* begin() const { 
      return data_;
  }
  const T* end() const { 
      return data_ + size_;
  }

  size_t Size() const { 
    return size_;
  }
  size_t Capacity() const { 
    return capacity_;
  }

  void PushBack(const T& value) { 
    if (size_ >= capacity_) {
      size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2; 
      T* new_data = new T[new_capacity];
      if (data_ != nullptr) {
        std::copy(data_, data_ + size_, new_data); 
        delete[] data_; 
      }
      data_ = new_data;
      capacity_ = new_capacity;
    }
    data_[size_] = value;
    size_++;
  }

private:
  T* data_;
  size_t size_;
  size_t capacity_;
};