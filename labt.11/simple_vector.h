#pragma once

#include <cstddef> // Для size_t
#include <algorithm> // Для std::copy

template<typename T>
class SimpleVector {
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size);
	SimpleVector(const SimpleVector& other);
	~SimpleVector();

	// Оголошення оператора присвоєння
	void operator=(const SimpleVector& other);

	T& operator[](size_t index);

	T* begin();
	T* end();
	const T* begin() const;
	const T* end() const;

	size_t Size() const;
	size_t Capacity() const;
	void PushBack(const T& value);

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) :
		data(new T[size]),
		size(size),
		capacity(size) {
}

template<typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other) :
		data(new T[other.capacity]),
		size(other.size),
		capacity(other.capacity) {
	std::copy(other.begin(), other.end(), begin());
}

// Реалізація оператора присвоєння
template<typename T>
void SimpleVector<T>::operator=(const SimpleVector& other) {
    // 1. Перевірка на самоприсвоєння
    if (this != &other) {
        // 2. Виділення нової пам'яті та копіювання (як у конструкторі копіювання)
        T* new_data = new T[other.capacity];
        std::copy(other.begin(), other.end(), new_data);

        // 4. Звільнення старої пам'яті
        delete[] data;

        // 5. Оновлення членів даних
        data = new_data;
        size = other.size;
        capacity = other.capacity;
    }
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
	delete[] data;
}

template<typename T>
T& SimpleVector<T>::operator[](size_t index) {
	return data[index];
}

template<typename T>
size_t SimpleVector<T>::Size() const {
	return size;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
	return capacity;
}

template<typename T>
void SimpleVector<T>::PushBack(const T& value) {
	if (size >= capacity) {
		auto new_cap = capacity == 0 ? 1 : 2 * capacity;
		auto new_data = new T[new_cap];
		std::copy(begin(), end(), new_data);
		delete[] data;
		data = new_data;
		capacity = new_cap;
	}
	data[size++] = value;
}

template<typename T>
T* SimpleVector<T>::begin() {
	return data;
}

template<typename T>
const T* SimpleVector<T>::begin() const {
	return data;
}

template<typename T>
T* SimpleVector<T>::end() {
	return data + size;
}

template<typename T>
const T* SimpleVector<T>::end() const {
	return data + size;
}