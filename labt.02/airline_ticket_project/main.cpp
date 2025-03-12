#include "test_runner.h"
#include "airline_ticket.h"

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
  return 0;
}