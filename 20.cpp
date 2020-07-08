#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

class Node {
 public:
  int data;
  Node* next;

  Node(int);
};

class LinkedList {
 private:
  Node* _head;
  Node* _tail;

  unsigned int _length;

 public:
  LinkedList();
  LinkedList(vector<int>);

  int append(int);
  int length();

  Node* intersection(LinkedList*);
};

ostream& operator<<(ostream& out, const Node* node) {
  out << node->data;
  return out;
}

Node::Node(int data) {
  this->data = data;
  this->next = NULL;
}

LinkedList::LinkedList() {
  this->_head = NULL;
  this->_tail = NULL;
  this->_length = 0;
};

LinkedList::LinkedList(vector<int> v) : LinkedList() {
  for (vector<int>::const_iterator it = v.cbegin(); it != v.cend(); ++it) {
    this->append(*it);
  }
};

int LinkedList::append(int data) {
  Node* node = new Node(data);
  if (this->_head == NULL) {
    this->_head = node;
    this->_tail = this->_head;
  } else {
    this->_tail->next = node;
    this->_tail = node;
  }
  return ++this->_length;
}

int LinkedList::length() { return this->_length; }

Node* LinkedList::intersection(LinkedList* other) {
  Node* curr_this = this->_head;
  Node* curr_that = other->_head;

  unsigned int len_this = this->length();
  unsigned int len_that = other->length();

  if (len_this > len_that) {
    for (int i = 0; i < len_this - len_that; i++) curr_this = curr_this->next;
  } else {
    for (int i = 0; i < len_that - len_this; i++) curr_that = curr_that->next;
  }

  while (curr_this->data != curr_that->data) {
    curr_this = curr_this->next;
    curr_that = curr_that->next;
  }

  return curr_this;
}

int main() {
  LinkedList* a = new LinkedList({3, 7, 8, 10});
  LinkedList* b = new LinkedList({99, 1, 8, 10});
  cout << a->intersection(b) << endl;
}