#include <cstddef>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;

    Node(int);
};

Node::Node(int data) {
    this->data = data;
    this->next = NULL;
}

struct LinkedList {
    Node *head;
    Node *tail;

    LinkedList();

    void insert(int);
    void append(int);

    void print();
};

LinkedList::LinkedList() {
    this->head = NULL;
    this->tail = NULL;
};

void LinkedList::insert(int data) {
    struct Node *node = new Node(data);

    if (this->head == NULL) {
        this->head = node;
        this->tail = this->head;
    } else {
        node->next = this->head;
        this->head = node;
    }
};

void LinkedList::append(int data) {
    struct Node *node = new Node(data);

    if (this->head == NULL) {
        this->head = node;
        this->tail = this->head;
    } else {
        this->tail->next = node;
        this->tail = node; 
    }
}

void LinkedList::print() {
    struct Node *curr = this->head;

    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
}

LinkedList partition(LinkedList list, int pivot) {
    LinkedList plist = LinkedList();
    struct Node *head = list.head;
    while (head != NULL) {
        int val = head->data;
        if (val < pivot) 
            plist.insert(val);
        else
            plist.append(val);
        head = head->next;
    }
    return plist;
}

int main() {
    LinkedList list = LinkedList();
    list.append(5);
    list.append(1);
    list.append(8);
    list.append(0);
    list.append(3);
    LinkedList plist = partition(list, 3);
    plist.print();
}