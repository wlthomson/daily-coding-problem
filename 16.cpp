#include <iostream>
#include <vector>

using namespace std;

class Log {
 private:
  int n;
  int curr;
  vector<int> buffer;

 public:
  Log(int n);

  int record(int order_id);
  int get_last(int i);

  friend ostream& operator<<(ostream& out, const Log* log);
};

Log::Log(int n) {
  this->n = n;
  this->curr = 0;
  this->buffer.resize(n);
};

int Log::record(int order_id) {
  this->buffer[this->curr] = order_id;
  ++this->curr %= this->n;
  return this->curr;
}

int Log::get_last(int i) {
  int last = this->curr + this->n - i;
  return this->buffer[last % this->n];
}

ostream& operator<<(ostream& out, const Log* log) {
  vector<int> buffer = log->buffer;
  size_t n = buffer.size();
  for (size_t i = 0; i < n; ++i) {
    if (i == 0) out << "[";
    out << buffer[i];
    if (i != n - 1)
      out << ", ";
    else
      out << "]";
  }
  return out;
}

int main() {
  int n = 7;
  vector<int> orders = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  Log* log = new Log(n);
  for (vector<int>::iterator it = orders.begin(); it != orders.end(); ++it) {
    log->record(*it);
  }

  cout << log << endl;
}
