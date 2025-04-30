#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

#include <cstddef> // Додано для використання size_t

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(std::size_t size) : data(new T[size]), capacity(size), size(size) {}
    ~SimpleVector() { delete[] data; }

    T& operator[](std::size_t index) { return data[index]; }

    T* begin() { return data; }
    T* end() { return data + size; }

    std::size_t Size() const { return size; }
    std::size_t Capacity() const { return capacity; }

    void PushBack(const T& value) {
        if (size >= capacity) {
            std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];
            for (std::size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size++] = value;
    }

private:
    T* data = nullptr;
    std::size_t capacity = 0;
    std::size_t size = 0;
};

#endif 