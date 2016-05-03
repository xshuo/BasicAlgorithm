#ifdef __1321__
#include <iostream>
#include <map>
#include <string>
#include <set>
#define N 10

int n, k;
int G[N][N];

int f_row[N];
int f_col[N];
int ret;

using std::set;
using std::map;
using std::string;
set<string> visit;

//not need
bool isdup() {
    string s = "";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (G[i][j])
                s += '1';
            else s += '0';
        }
    }
    if (visit.find(s) != visit.end())
        return true;
    else
        visit.insert(s);
    return false;
}

void dfs(int ind_k, int s_row) {
    if (ind_k > k) {
        ret++;
        return;
    }
    for (int i = s_row; i <= n - k + ind_k; i++) {
        if (!f_row[i]){
            f_row[i] = 1;
            for (int j = 1; j <= n; j++) {
                if (!f_col[j] && !G[i][j]) {
                    f_col[j] = 1;
                    dfs(ind_k + 1, i + 1);
                    f_col[j] = 0;
                }
            }
            f_row[i] = 0;
        }
    }
}

int main(int argc, char** args) {
    while(scanf("%d%d", &n, &k)) {
        if (n == -1 && k == -1)
            break;
        getchar();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                char s;
                scanf("%c", &s);
                if (s == '.')
                    G[i][j] = 1;
                else
                    G[i][j] = 0;
            }
            getchar();
        }
        memset(f_row, 0, sizeof(f_row));
        memset(f_col, 0, sizeof(f_col));
        ret = 0;
        visit.clear();
        dfs(1, 1);
        printf("%d\n", ret);
    }
}
#endif