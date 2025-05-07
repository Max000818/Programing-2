#include "test_runner.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList() {
    while (head) {
      PopFront();
    }
  }

  void PushFront(const T& value) {
    Node* new_node = new Node{value, head};
    head = new_node;
  }

  void InsertAfter(Node* node, const T& value) {
    if (node == nullptr) {
      PushFront(value);
      return;
    }
    Node* new_node = new Node{value, node->next};
    node->next = new_node;
  }

  void RemoveAfter(Node* node) {
    if (node == nullptr) {
      PopFront();
      return;
    }
    if (node->next == nullptr) {
      return;
    }
    Node* node_to_remove = node->next;
    node->next = node_to_remove->next;
    delete node_to_remove;
  }

  void PopFront() {
    if (head == nullptr) {
      return;
    }
    Node* old_head = head;
    head = head->next;
    delete old_head;
  }

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

// Тести залишаються незмінними
void TestPushFront() { /* ... */ }
void TestInsertAfter() { /* ... */ }
void TestRemoveAfter() { /* ... */ }
void TestPopFront() { /* ... */ }

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}