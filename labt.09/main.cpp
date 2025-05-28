#include "test_runner.h"
#include "profile.h"
#include "stack_vector.h"

#include <vector>
#include <string>
#include <stdexcept>

// Юніт-тест для перевірки конструктора та методів Size/Capacity.
void TestConstruction() {
    StackVector<int, 10> v;
    ASSERT_EQUAL(v.Size(), 0u);
    ASSERT_EQUAL(v.Capacity(), 10u);

    StackVector<int, 8> u(5);
    ASSERT_EQUAL(u.Size(), 5u);
    ASSERT_EQUAL(u.Capacity(), 8u);

    try {
        StackVector<int, 10> v_err(11);
        Assert(false, "Constructor should throw invalid_argument");
    } catch (std::invalid_argument&) {
        // Очікуваний виняток
    } catch (...) {
        Assert(false, "Caught wrong exception in constructor test");
    }
}

// Юніт-тест для перевірки методу PushBack.
void TestPushBack() {
    StackVector<int, 5> v;
    for (size_t i = 0; i < 5; ++i) {
        v.PushBack(static_cast<int>(i));
    }

    ASSERT_EQUAL(v.Size(), 5u);
    ASSERT_EQUAL(v.Capacity(), 5u);

    for (size_t i = 0; i < 5; ++i) {
        ASSERT_EQUAL(v[i], static_cast<int>(i));
    }

    try {
        v.PushBack(5);
        Assert(false, "PushBack should throw overflow_error");
    } catch (std::overflow_error&) {
        // Очікуваний виняток
    } catch (...) {
        Assert(false, "Caught wrong exception in PushBack test");
    }
}

// Юніт-тест для перевірки методу PopBack.
void TestPopBack() {
    StackVector<int, 5> v;
    for (size_t i = 0; i < 5; ++i) {
        v.PushBack(static_cast<int>(i));
    }

    ASSERT_EQUAL(v.PopBack(), 4);
    ASSERT_EQUAL(v.PopBack(), 3);
    ASSERT_EQUAL(v.Size(), 3u);

    v.PopBack();
    v.PopBack();
    v.PopBack();

    ASSERT_EQUAL(v.Size(), 0u);

    try {
        v.PopBack();
        Assert(false, "PopBack should throw underflow_error");
    } catch (std::underflow_error&) {
        // Очікуваний виняток
    } catch (...) {
        Assert(false, "Caught wrong exception in PopBack test");
    }
}

// Функція для запуску всіх тестів.
void RunAllTests() {
    TestRunner tr;
    RUN_TEST(tr, TestConstruction);
    RUN_TEST(tr, TestPushBack);
    RUN_TEST(tr, TestPopBack);
}

// Функція для запуску бенчмарку.
void RunBenchmark() {
    cerr << "Running benchmark..." << endl;
    const size_t N = 50000; // Кількість елементів для бенчмарку

    {
        LOG_DURATION("vector w/o reserve");
        vector<int> v;
        for (size_t i = 0; i < N; ++i) {
            v.push_back(i);
        }
    }

    {
        LOG_DURATION("vector with reserve");
        vector<int> v;
        v.reserve(N);
        for (size_t i = 0; i < N; ++i) {
            v.push_back(i);
        }
    }

    {
        LOG_DURATION("StackVector");
        StackVector<int, N> sv;
        for (size_t i = 0; i < N; ++i) {
            sv.PushBack(i);
        }
    }
    cerr << "Done" << endl;
}

int main() {
    RunAllTests();
    RunBenchmark();
    return 0;
}