#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string>& v) {
  size_t n = v.size();
  for (size_t i = 0; i < n; ++i) {
    if (i == 0) out << "[";
    out << v[i];
    if (i != n - 1)
      out << ", ";
    else
      out << "]";
  }
  return out;
}

struct BinaryNode {
  string val;
  BinaryNode* left;
  BinaryNode* right;

  BinaryNode(string);
  BinaryNode(string, BinaryNode*, BinaryNode*);
};

BinaryNode::BinaryNode(string val) {
  this->val = val;
  this->left = nullptr;
  this->right = nullptr;
};

BinaryNode::BinaryNode(string val, BinaryNode* left, BinaryNode* right) {
  this->val = val;
  this->left = left;
  this->right = right;
};

string serialise(BinaryNode* root) {
  if (root == nullptr) return "#";
  return root->val + " " + serialise(root->left) + " " + serialise(root->right);
}

BinaryNode* deserialiser(vector<string>::iterator it) {
  function<BinaryNode*()> deserialise = [&deserialise, &it]() -> BinaryNode* {
    string val = *it++;
    if (val == "#") return nullptr;
    BinaryNode* node = new BinaryNode(val);
    node->left = deserialise();
    node->right = deserialise();
    return node;
  };
  return deserialise();
}

BinaryNode* deserialise(string data) {
  stringstream ss(data);
  istream_iterator<string> begin(ss);
  istream_iterator<string> end;
  vector<string> nodes(begin, end);
  vector<string>::iterator it_nodes = nodes.begin();
  return deserialiser(it_nodes);
}

int main() {
  BinaryNode* root = new BinaryNode("root");
  BinaryNode* left = new BinaryNode("left");
  BinaryNode* left_left = new BinaryNode("left.left");
  BinaryNode* right = new BinaryNode("right");

  root->left = left;
  root->left->left = left_left;
  root->right = right;

  cout << serialise(root) << endl;
  cout << serialise(deserialise(serialise(root))) << endl;
}