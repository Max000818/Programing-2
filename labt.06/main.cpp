#include "SimpleVector.h"
#include <iostream>

void TestConstruction() {
    SimpleVector<int> vec(5);
    if (vec.Size() == 5 && vec.Capacity() == 5) {
        std::cout << "TestConstruction OK\n";
    } else {
        std::cout << "TestConstruction FAIL\n";
    }
}

void TestPushBack() {
    SimpleVector<int> vec;
    vec.PushBack(10);
    vec.PushBack(20);
    if (vec.Size() == 2 && vec[0] == 10 && vec[1] == 20) {
        std::cout << "TestPushBack OK\n";
    } else {
        std::cout << "TestPushBack FAIL\n";
    }
}

int main() {
    TestConstruction();
    TestPushBack();
    return 0;
}