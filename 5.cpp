#include <functional>
#include <iostream>

using namespace std;

function<int(function<int(int, int)>)> cons(int a, int b) { return [&a, &b](function<int(int, int)> f) -> int { return f(a, b); }; }
int car(function<int(function<int(int, int)>)> pair) { return pair([](int a, int b) -> int { return a; }); }
int cdr(function<int(function<int(int, int)>)> pair) { return pair([](int a, int b) -> int { return b; }); }

int main() {
    cout << car(cons(3, 4)) << endl;
    cout << cdr(cons(3, 4)) << endl;
}