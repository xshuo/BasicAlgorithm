#ifdef _3259_wormholes_
#include <stdio.h>
#include <string.h>

#define N 510
#define M 6000
#define MAX_INT 1 << 25

typedef struct Edge {
    int v1, v2;
    int value;
} Edge;

Edge edge[M];
int V, E;
int d[N], pi[N];

bool bellman_ford(int s) {
    int i, j;
    for (i = 1; i <= V; ++i) {
        d[i] = MAX_INT;
        pi[i] = -1;
    }
    d[s] = 0;
    for (i = 1; i <= V - 1; ++i) {
        for (j = 0; j < E; ++j) {
            if (d[edge[j].v1] + edge[j].value < d[edge[j].v2]) {
                d[edge[j].v2] = d[edge[j].v1] + edge[j].value;
                pi[edge[j].v2] = edge[j].v1;
            }
        }
    }
    for (i = 0; i < E; ++i) {
        if (d[edge[i].v2] > d[edge[i].v1] + edge[i].value)
            return true;
    }
    return false;
}

int main(int argc, char** args) {
    int num;
    int w;
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    scanf("%d", &num);
    while (num--) {
        scanf("%d%d%d", &V, &E, &w);
        int i, j = 0;
        int s, e, v;
        for (i = 0; i < E; ++i) {            
            scanf("%d%d%d", &s, &e, &v);
            edge[j].v1 = s;
            edge[j].v2 = e;
            edge[j++].value = v;

            edge[j].v1 = e;
            edge[j].v2 = s;
            edge[j++].value = v;
        }
        for (i = 0; i < w; ++i) {
            scanf("%d%d%d", &s, &e, &v);
            edge[j].v1 = s;
            edge[j].v2 = e;
            edge[j++].value = -v;
        }
        E = 2 * E + w;
        printf("%s\n", bellman_ford(1) ? "YES" : "NO");
    }
}
#endif