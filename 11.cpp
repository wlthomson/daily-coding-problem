#include <iostream>
#include <unordered_map>
using namespace std;

int const MAX_TREE_WIDTH = 26;

int getCharIndex(char c) { return c - 'a'; }
char getIndexChar(int i) { return 'a' + i; };

struct TrieNode {
    struct TrieNode *nodes[MAX_TREE_WIDTH];
    bool isTerminal;

    TrieNode();

    void insert(string);
    struct TrieNode* search(string);
    void iterate(string);
    void query(string);
};

TrieNode::TrieNode() {
    for (int i=0; i<MAX_TREE_WIDTH; i++) { 
        this->nodes[i] = nullptr;
    }
    this->isTerminal = false;
}

void TrieNode::insert(string str) {
    struct TrieNode *curr = this;
    for (int i=0; i<str.length(); i++) {
        int index = getCharIndex(str[i]);
        if (!curr->nodes[index]) {
            curr->nodes[index] = new TrieNode();
        }
        curr = curr->nodes[index];
    }
    curr->isTerminal = true;
}

struct TrieNode* TrieNode::search(string str) {
    struct TrieNode *curr = this;
    for (int i=0; i<str.length(); i++) {
        int index = getCharIndex(str[i]);
        if (!curr->nodes[index]) { return nullptr; }
        curr = curr->nodes[index];
    }
    return curr;
}

void TrieNode::iterate(string str) {
    if (this->isTerminal) { cout << str << endl; }
    for (int i=0; i<MAX_TREE_WIDTH; i++) {
        if (this->nodes[i] != nullptr) {
            this->nodes[i]->iterate(str + getIndexChar(i));
        }
    }
}

void TrieNode::query(string str) {
    struct TrieNode *node = this->search(str);
    if (node != nullptr) { node->iterate(str); }
}


int main() {}