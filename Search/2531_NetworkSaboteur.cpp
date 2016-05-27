#ifdef __2531__
#include <iostream>

#define MAX_N 25
int mN;
bool sub[MAX_N];

int graph[MAX_N][MAX_N];

int ret = -1;

int traffic(bool sub[], int n) {
    int sum = 0;
    for (int i = 1; i <= n; i ++) {
        if (!sub[i]) {
            for (int j = 1; j <= n; j++) {
                if (sub[j])
                    sum += graph[i][j];
            }
        }
    }
    return sum;
}

void dfs_sub(int start, int n, bool sub[], int selected) {
    if (selected > n / 2)
        return;
    if (start > n) {
        int sum = traffic(sub, n);
        if (sum > ret)
            ret = sum;
        return;
    }
    sub[start] = false;
    dfs_sub(start + 1, n, sub, selected);
    
    sub[start] = true;
    dfs_sub(start + 1, n, sub, selected + 1);
}

int main(int argc, char** args) {
    scanf("%d", &mN);
    for (int i = 1; i <= mN; i++) {
        for (int j = 1; j <= mN; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    memset(sub, 0, sizeof(sub));
    dfs_sub(1, mN, sub, 0);
    printf("%d\n", ret);
}
#endif

