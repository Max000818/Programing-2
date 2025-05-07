#include "simple_vector.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
#include <vector> 

using namespace std;

void TestConstruction() {
  SimpleVector<int> empty;
  assert(empty.Size() == 0);
  assert(empty.Capacity() == 0);
  assert(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  assert(five_strings.Size() == 5);
  assert(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    assert(item.empty());
  }
  five_strings[2] = "Hello";
  assert(five_strings[2] == "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    assert(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Додано std::
  assert(v.Size() == expected.size());
  assert(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestConstruction();
  TestPushBack();
  cout << "All tests passed!" << endl;
  return 0;
}