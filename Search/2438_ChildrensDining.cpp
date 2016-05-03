#ifdef __2438__
//哈密顿回路严格说算是NP问题，没有多项式解
/****
所以，直接做完全搜索，TLE，但就针对这个题目来说，针对有些条件，用定理可以判定是否一定存在
哈密顿回路，如果一定存在就可以用一些构造的方法构造出哈密顿回路，这个可以到O(n^2)
****/
#include <iostream>

#define MAX_N 410
int n;
int graph[MAX_N][MAX_N];
int path[MAX_N];
bool visit[MAX_N];

bool is_safe(int prev, int current, int v) {
    if (graph[prev][current])
        return false;
    //for (int i = 1; i < v ; i++) 
        //if (path[i] == current)
            //return false;
    if (visit[current])
        return false;
    return true;
}

bool dfs(int path[], int v, const int n) {
    if (v > n) {
        if (!graph[path[v - 1]][path[1]])
            return true;
        return false;
    }
    for (int i = 1; i <= n; i++) {
        if (is_safe(path[v - 1], i, v)) {
            path[v] = i;
            visit[i] = true;
            if (dfs(path, v + 1, n) == true)
                return true;
            else {
                path[v] = -1;
                visit[i] = false;
            }
        }
    }
    return false;
}

int main(int argc, char** args) {
    int m;
    while (scanf("%d%d", &n, &m)) {
        if (n == 0) break;
        n = 2 * n;
        memset(graph, 0, sizeof(graph));
        memset(path, 0xff, sizeof(path));
        memset(visit, 0, sizeof(visit));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            graph[a][b] = graph[b][a] = 1;
        }
        path[1] = 1;
        visit[1] = true;
        if (dfs(path, 2, n)) {
            for (int i = 1; i <= n; i++) {
                printf("%d ", path[i]);
            }
            printf("\n");
        } else printf("No solution!\n");
    }
    return 0;
}
#endif