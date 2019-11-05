#include <iostream>
using namespace std;

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int lcs(char *u, char *v, char *w, int x, int y, int z) {
    int l[x+1][y+1][z+1];
    for (int i=0; i<=x; i++) {
        for (int j=0; j<=y; j++) {
            for (int k=0; k<=z; k++) {
                if (i == 0 || j == 0 || k == 0)
                    l[i][j][k] = 0;
                else if (u[i-1] == v[j-1] && u[i-1] == w[k-1])
                    l[i][j][k] = l[i-1][j-1][k-1] + 1;
                else 
                    l[i][j][k] = max(max(l[i-1][j][k], l[i][j-1][k]), l[i][j][k-1]); 
            }
        }
    }
    return l[x][y][z];
}

int main() {
    char u[] = "epidemiologist";
    char v[] = "refrigeration";
    char w[] = "supercalifragilisticexpialodocious";

    int x = strlen(u);
    int y = strlen(v);
    int z = strlen(w);

    cout << lcs(u, v, w, x, y, z) << endl;
}

