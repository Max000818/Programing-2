#include "student.h"
#include "test_runner.h"
#include "profile.h"

#include <algorithm>

using namespace std;

bool Compare(const Student& first, const Student& second) {
  return first.rating > second.rating;
}

void TestComparison() {
  Student newbie {
    "Ivan", "Ivanov", {
      {"C++", 1.0},
      {"Algorithms", 3.0}
    },
    2.0
  };

  Student cpp_expert {
    "Petr", "Petrov", {
      {"C++", 9.5},
      {"Algorithms", 6.0}
    },
    7.75
  };

  Student guru {
    "Stepan", "Stepanov", {
      {"C++", 10.0},
      {"Algorithms", 10.0}
    },
    10.0
  };
  ASSERT(Compare(guru, newbie));
  ASSERT(Compare(guru, cpp_expert));
  ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
  vector<Student> students {
    {"Stepan", "Stepanov", {{"Maths", 2.}}, 2.},
    {"Semen", "Semenov", {{"Maths", 4.}}, 4.},
    {"Ivan", "Ivanov", {{"Maths", 5.}}, 5.},
    {"Petr", "Petrov", {{"Maths", 3.}}, 3.},
    {"Alexander", "Alexandrov", {{"Maths", 1.}}, 1.}
  };
  sort(students.begin(), students.end(), Compare);
  ASSERT(is_sorted(students.begin(), students.end(),
    [](const Student& first, const Student& second) {
      return first.rating > second.rating;
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestComparison);
  RUN_TEST(tr, TestSorting);

  {
    LOG_DURATION("Sorting 25000 students");
    vector<Student> large_group;
    for (int i = 0; i < 25000; ++i) {
      large_group.push_back({
        "FirstName" + to_string(i),
        "LastName" + to_string(i),
        {{"Math", i % 10 + 1}},
        i % 10 + 1
      });
    }
    sort(large_group.begin(), large_group.end(), Compare);
  }
  
  return 0;
}