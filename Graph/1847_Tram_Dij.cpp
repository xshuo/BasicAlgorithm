#include <iostream>
#include <limits>

#define N 110

int G[N][N];
int dis[N];
int pre[N];

void Dijk(int src, int count) {
    int q[N];//
    for (int i = 0; i < N; i++) {
        dis[i] = INT_MAX;
        q[i] = INT_MAX;
        pre[i] = INT_MAX;
    }
    q[src] = 0;

    while (1) {
        int i, n = 0, min_dis = INT_MAX;
        for (i = 1; i <= count; i++) {
            if (q[i] != -1 && q[i] < min_dis) {
                n = i;
                min_dis = q[i];
            }
        }
        if (n == 0) break;
        dis[n] = q[n];

        for (i = 1; i <= count; i++) {
            if (G[n][i] != -1) {
                if (q[i] > q[n] + G[n][i]) {
                    q[i] = q[n] + G[n][i];
                    pre[i] = n;
                }
            }
        }
        q[n] = -1; //remove from the queue
    }
}

int main(int argc, char** args) {
    int COUNT, A, B;
    scanf("%d%d%d", &COUNT, &A, &B);
    memset(G, 0xff, sizeof(G));
    for (int i = 1; i <= COUNT; i++) {
        int cnt, t;
        scanf("%d", &cnt);
        for (int j = 1; j <= cnt; j++) {
            scanf("%d", &t);
            if (j == 1)
                G[i][t] = 0;
            else
                G[i][t] = 1;
        }
    }
    Dijk(A, COUNT);
    if (dis[B] == INT_MAX)
        printf("%d\n", -1);
    else
        printf("%d\n", dis[B]);
    return 0;
}