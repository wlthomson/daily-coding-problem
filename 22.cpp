#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const unordered_map<int, string>& m) {
  size_t n = m.size();
  int i = 0;
  for (unordered_map<int, string>::const_iterator it = m.cbegin();
       it != m.cend(); ++it) {
    if (i == 0) out << "[";
    cout << "(";
    out << it->first;
    out << ": ";
    out << it->second;
    out << ")";
    if (i++ != n - 1)
      out << ", ";
    else
      out << "]";
  }
  return out;
}
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

// Recursion, no memoisation.
//
// Time: O(2^n)
vector<string> extract_words_rec(set<string> word_list, string word_string) {
  vector<string> words;
  if (word_string.length() == 0) return words;
  for (int curr_position = 0; curr_position < word_string.length();
       ++curr_position) {
    string prefix = word_string.substr(0, curr_position + 1);
    string suffix = word_string.substr(curr_position + 1);
    set<string>::iterator it = word_list.find(prefix);
    if (it != word_list.end()) {
      vector<string> other_words = extract_words_rec(word_list, suffix);
      if (other_words.size() > 0 || suffix.length() == 0) {
        words.push_back(prefix);
        words.insert(words.end(), other_words.begin(), other_words.end());
        return words;
      }
    }
  }
  return words;
}

// DP, memoise words found before given index.
//
// Time: O(n^2)
vector<string> extract_words_dp(set<string> word_list, string word_string) {
  int letter_count = word_string.length();
  unordered_map<int, string> previous_words = {pair<int, string>(0, "")};
  for (int curr_position = 0; curr_position <= letter_count; ++curr_position) {
    unordered_map<int, string> new_previous_words = previous_words;
    for (unordered_map<int, string>::iterator it_m = previous_words.begin();
         it_m != previous_words.end(); ++it_m) {
      int previous_position = it_m->first;
      string word = word_string.substr(previous_position,
                                       curr_position - previous_position);
      set<string>::iterator it_s = word_list.find(word);
      if (it_s != word_list.end()) {
        new_previous_words[curr_position] = word;
      }
    }
    previous_words = new_previous_words;
  }

  vector<string> words;
  if (previous_words.find(letter_count) == previous_words.end()) return words;
  while (letter_count > 0) {
    string word = previous_words.find(letter_count)->second;
    letter_count -= word.length();
    words.push_back(word);
  }
  reverse(words.begin(), words.end());
  return words;
}

int main() {
  set<string> word_list = {"brown", "fox", "quick", "the"};
  string word_string = "thequickbrownfox";
  cout << extract_words_rec(word_list, word_string) << endl;
  cout << extract_words_dp(word_list, word_string) << endl;
}