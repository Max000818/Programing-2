#pragma once

#include <stdexcept> // Для std::invalid_argument, std::overflow_error, std::underflow_error
#include <cstddef>   // Для size_t

template <typename T, size_t N>
class StackVector {
public:
    /**
     * @brief Конструктор. Створює StackVector заданого розміру.
     * @param a_size Початковий розмір вектора. За замовчуванням 0.
     * @throws std::invalid_argument якщо a_size перевищує ємність N.
     */
    explicit StackVector(size_t a_size = 0) : size_(a_size) {
        if (a_size > N) {
            throw std::invalid_argument("Initial size exceeds capacity");
        }
        // Елементи T data_[N] будуть ініціалізовані за замовчуванням.
    }

    /**
     * @brief Оператор доступу до елемента за індексом (для читання та запису).
     * @param index Індекс елемента.
     * @return Посилання на елемент.
     */
    T& operator[](size_t index) {
        return data_[index];
    }

    /**
     * @brief Оператор доступу до елемента за індексом (тільки для читання).
     * @param index Індекс елемента.
     * @return Константне посилання на елемент.
     */
    const T& operator[](size_t index) const {
        return data_[index];
    }

    /**
     * @brief Повертає вказівник на початок вектора.
     * @return Вказівник на перший елемент.
     */
    T* begin() {
        return data_;
    }

    /**
     * @brief Повертає вказівник на елемент, що йде за останнім.
     * @return Вказівник на елемент за останнім.
     */
    T* end() {
        return data_ + size_;
    }

    /**
     * @brief Повертає константний вказівник на початок вектора.
     * @return Константний вказівник на перший елемент.
     */
    const T* begin() const {
        return data_;
    }

    /**
     * @brief Повертає константний вказівник на елемент, що йде за останнім.
     * @return Константний вказівник на елемент за останнім.
     */
    const T* end() const {
        return data_ + size_;
    }

    /**
     * @brief Повертає поточний розмір вектора.
     * @return Кількість елементів у векторі.
     */
    size_t Size() const {
        return size_;
    }

    /**
     * @brief Повертає максимальну ємність вектора.
     * @return Ємність вектора (N).
     */
    size_t Capacity() const {
        return N;
    }

    /**
     * @brief Додає елемент в кінець вектора.
     * @param value Значення, яке потрібно додати.
     * @throws std::overflow_error якщо вектор повний.
     */
    void PushBack(const T& value) {
        if (size_ >= N) {
            throw std::overflow_error("Cannot push back: StackVector is full");
        }
        data_[size_++] = value;
    }

    /**
     * @brief Видаляє останній елемент з вектора та повертає його.
     * @return Значення останнього елемента.
     * @throws std::underflow_error якщо вектор порожній.
     */
    T PopBack() {
        if (size_ == 0) {
            throw std::underflow_error("Cannot pop back: StackVector is empty");
        }
        --size_;
        return data_[size_];
    }

private:
    T data_[N];      // Масив для зберігання даних.
    size_t size_ = 0; // Поточний розмір вектора.
};