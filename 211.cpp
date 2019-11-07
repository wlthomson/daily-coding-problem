#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int rkval(char a, int k) { 
    return pow(26, k) * (a - 'a' + 1);
}

int rkhash(int p, char s, char c, int k) {
    return (p - rkval(s, k-1)) * 26 + rkval(c, 0);
}

vector<int> rk(string p, string s) {
    vector<int> m;

    int k = p.length();
    int l = s.length();

    if (k <= l) {
        int pv = 0;
        int hv = 0;
        for (int i = 0; i < k; i++) {
            pv += rkval(p[i], k - i - 1);
            hv += rkval(s[i], k - i - 1);
        }

        if (pv == hv) {
            if (s.substr(0, k) == p)
                m.push_back(0);
        }

        for (int i=0; i<=(s.length()-k); i++) {    
            hv = rkhash(hv, s[i], s[i+k], k);
            if (pv == hv) {
                if (s.substr(i+1, k) == p) {
                    m.push_back(i+1);
                }
            }
        }

    }

    return m;
}

int main() {
    vector<int> m = rk("abr", "abracadabra");
    copy(m.begin(),m.end(),ostream_iterator<int>(cout, " "));
}
