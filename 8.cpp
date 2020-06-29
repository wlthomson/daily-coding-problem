#include <iostream>

using namespace std;

struct Node {
  int key;
  Node* left;
  Node* right;

  Node(int);
};

Node::Node(int key) {
  this->key = key;
  this->left = nullptr;
  this->right = nullptr;
};

bool count_unival(Node* root, int* const count) {
  if (root == nullptr) {
    *count = 0;
    return true;
  }
  int countLeft, countRight;
  const bool isUnivalLeft = count_unival(root->left, &countLeft);
  const bool isUnivalRight = count_unival(root->right, &countRight);
  const int countTotal = countLeft + countRight;
  if (isUnivalLeft && isUnivalRight) {
    bool isKeyEqualLeft = root->left == nullptr || root->key == root->left->key;
    bool isKeyEqualRight =
        root->right == nullptr || root->key == root->right->key;
    if (isKeyEqualLeft && isKeyEqualRight) {
      *count = countTotal + 1;
      return true;
    }
    *count = countTotal;
    return false;
  }
  *count = countTotal;
  return false;
}

int main() {
  struct Node* root = new Node(1);
  struct Node* rootLeft = new Node(3);
  struct Node* rootRight = new Node(2);
  struct Node* rootRightLeft = new Node(2);
  struct Node* rootRightRight = new Node(2);
  struct Node* rootRightRightRight = new Node(2);

  root->left = rootLeft;
  root->right = rootRight;
  rootRight->left = rootRightLeft;
  rootRight->right = rootRightRight;
  rootRightRight->right = rootRightRightRight;

  int countUnival;
  const bool isUnival = count_unival(root, &countUnival);

  cout << dec << countUnival << endl;
}