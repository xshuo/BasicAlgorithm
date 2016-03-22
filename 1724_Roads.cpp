#ifdef __1011_ROADS__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 101
#define MAX_R 10000

typedef struct Node {
    int des;
    int L;
    int T;
    Node* next;
} Node;

Node cities[MAX_N];
int city_color[MAX_N];

int K, N;

int current_k;
int current_dis;

int min_dis;

void dfs_road(int start) {
    if (start == N) {
        if (current_k <= K && current_dis < min_dis)
            min_dis = current_dis;
        return;
    }
    if (current_k > K)
        return;
    if (current_dis > min_dis)
        return;

    Node* road = cities[start].next;
    while (road) {
        if (city_color[road->des] == 1) {
            road = road->next;
            continue;
        }
        city_color[road->des] = 1;
        current_dis += road->L;
        current_k += road->T;

        dfs_road(road->des);

        city_color[road->des] = 0;
        current_dis -= road->L;
        current_k -= road->T;

        road = road->next;
    }
}

int main(int argc, char** args) {
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    int R;
    int S, D, L, T;

    current_k = 0;
    current_dis = 0;
    min_dis = 1 << 30;
    memset(cities, 0, sizeof(cities));
    memset(city_color, 0, sizeof(city_color));

    scanf("%d%d%d", &K, &N, &R);
    for (int i = 0; i < R; i++) {
        scanf("%d%d%d%d", &S, &D, &L, &T);
        bool bad_road = false;
        Node* road = cities[S].next;
        while (road) {            
            if (road->des == D) {
                if (L > road->L && T > road->T) {
                    bad_road = true;
                    break;
                }
            }
            road = road->next;
        }
        if (bad_road) continue;
        road = (Node*)malloc(sizeof(Node));
        road->des = D;
        road->L = L;
        road->T = T;
        road->next = cities[S].next;
        cities[S].next = road;
    }

    city_color[1] = 1;
    dfs_road(1);
    city_color[1] = 0;

    if (min_dis == 1 << 30)
        min_dis = -1;
    printf("%d\n", min_dis);
    return 1;
}
#endif