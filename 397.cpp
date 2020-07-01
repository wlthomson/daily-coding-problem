#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

typedef struct {
  int start, end;
} job;

ostream& operator<<(ostream& out, const vector<job>& v) {
  size_t n = v.size();
  for (size_t i = 0; i < n; ++i) {
    if (i == 0) out << "[";
    out << "(";
    out << v[i].start;
    out << ", ";
    out << v[i].end;
    out << ")";
    if (i != n - 1)
      out << ", ";
    else
      out << "]";
  }
  return out;
}

bool comparator(job a, job b) { return a.end < b.end; }

vector<job> get_max_jobs(const vector<job> jobs) {
  vector<job> sorted_jobs(jobs.begin(), jobs.end());
  sort(sorted_jobs.begin(), sorted_jobs.end(), comparator);
  vector<job> max_jobs;
  for (vector<job>::const_iterator cit = sorted_jobs.cbegin();
       cit != sorted_jobs.cend(); ++cit) {
    if (max_jobs.empty() || (cit->start >= max_jobs.back().end))
      max_jobs.push_back(*cit);
  }
  return max_jobs;
}

int main() {
  vector<job> jobs = {{0, 6}, {1, 4}, {3, 5},  {3, 8},
                      {4, 7}, {5, 9}, {6, 10}, {8, 11}};
  vector<job> max_jobs = get_max_jobs(jobs);
  cout << max_jobs << endl;
}
