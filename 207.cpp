#include <iostream>
#include <list>
#include <vector>
using namespace std;

bool is_bipartite(vector<vector<int> > g) {
    int v = 0;
    const int s = g.size();

    vector<int> c(s, 0);
    list<int> q;

    c[v] = 1;
    q.push_back(v);

    while(!q.empty()) {
        v = q.front();
        q.pop_front();

        for (vector<int>::iterator it = g[v].begin(); it != g[v].end(); ++it) {
            if (c[*it] == 0) {
                c[*it] = -c[v];
                q.push_back(*it);
            } else if (c[*it] == c[v]) return false;
        }
    }
    return true;
}


int main() {
    vector<vector<int> > g;

    g.push_back(vector<int>(2));
    g.push_back(vector<int>(2));
    g.push_back(vector<int>(3));
    g.push_back(vector<int>(1));

    g[0][0]=1;
    g[0][1]=2;
    g[1][0]=0;
    g[1][1]=1;
    g[2][0]=0;
    g[2][1]=1;
    g[2][2]=3;
    g[3][0]=2;

    cout << boolalpha << is_bipartite(g) << endl;
}
