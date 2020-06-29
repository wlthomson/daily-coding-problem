#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *both;

  Node(int);
};

Node::Node(int data) {
  this->data = data;
  this->both = nullptr;
};

struct XORLinkedList {
  Node *head;
  Node *tail;

  XORLinkedList();

  Node *XOR(Node *x, Node *y);

  void insert(int);
  void append(int);

  void print();
};

XORLinkedList::XORLinkedList() {
  this->head = NULL;
  this->tail = NULL;
};

Node *XORLinkedList::XOR(Node *x, Node *y) {
  return (Node *)((uintptr_t)(x) ^ (uintptr_t)(y));
}

void XORLinkedList::insert(int data) {
  // New node link is XOR of null and current head.
  struct Node *node = new Node(data);
  node->both = XOR(nullptr, this->head);

  if (this->head) {
    // Previous head node link is XOR of new node and next node.
    this->head->both = XOR(node, XOR(this->head->both, nullptr));
    this->head = node;
  } else {
    this->head = node;
    this->tail = this->head;
  }
};

void XORLinkedList::append(int data) {
  // New node link is XOR of current tail and null.
  struct Node *node = new Node(data);
  node->both = XOR(this->tail, nullptr);

  if (this->head) {
    // Previous tail node link is XOR of previous node and new node.
    this->tail->both = XOR(XOR(this->tail->both, nullptr), node);
    this->tail = node;
  } else {
    this->head = node;
    this->tail = this->head;
  }
}

void XORLinkedList::print() {
  Node *curr = this->head;
  Node *prev = nullptr;
  Node *next;

  while (curr != nullptr) {
    next = XOR(prev, curr->both);

    cout << curr->data;
    if (next != nullptr) {
      cout << " -> ";
    }

    prev = curr;
    curr = next;
  }
}

int main() {
  XORLinkedList list = XORLinkedList();
  list.append(3);
  list.insert(2);
  list.append(4);
  list.append(5);
  list.insert(1);
  list.print();
}