//#define __1190_BIRTHDAY_CAKE__
#ifdef __1190_BIRTHDAY_CAKE__

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_VALUE 0x7fffffff
#define MAX_FLOOR 21

int min_floor_v[MAX_FLOOR];
int min_floor_s[MAX_FLOOR];

//#define DFS_DEBUG
#ifdef DFS_DEBUG
typedef struct cake {
    int r, h;
}Cake;

Cake debug_cake[21];
int debug_cake_top;
void print_cake() {
    printf("=========================================\n");
    for (int i = 0; i < debug_cake_top; i++) {
        printf("%d %d\n", debug_cake[i].r, debug_cake[i].h);
    }
    printf("=========================================\n");    
}
#endif


int N, M;

int min_area = MAX_VALUE;

int max_v(int m, int r, int h) {
    int v = 0;
    for (int i = 0; i < m; i++) {
        v += (r - i) * (r - i) * (h - i);
    }
    return v;
}

void dfs_cake(int max_r, int max_h, int m, int v, int s) {
    if (m == 0) {
        if (v == N && s < min_area) {
#ifdef DFS_DEBUG
            print_cake();
#endif
            min_area = s;
        }
        return;
    }

    if (max_r < m || max_h < m)
        return;
    if (s + min_floor_s[m] > min_area)
        return;
    if (v + min_floor_v[m] > N)
        return;
    if (max_v(m, max_r, max_h) < N - v)
        return;

    for (int i = max_r; i >= m; i--) 
    {
        if (m == M) s = i * i;
        for (int j = max_h; j >= m; j--) 
        {
#ifdef DFS_DEBUG
            debug_cake[debug_cake_top].r = i;
            debug_cake[debug_cake_top++].h = j;
#endif
            dfs_cake(i - 1, j - 1, m - 1, v + i * i * j, s + 2 * i * j);

#ifdef DFS_DEBUG
            debug_cake_top--;
#endif
        }
    }
}



int main(int argc, char** args) {
    scanf("%d%d", &N, &M);
    int max_r, max_h;
    max_h = N;
    max_r = (int)floor(sqrt(N * 1.0));

    min_floor_v[0] = 0;
    min_floor_s[0] = 0;
    for (int i = 1; i <= M; i++) {
        min_floor_v[i] = min_floor_v[i - 1] + i * i * i;
        min_floor_s[i] = min_floor_s[i - 1] + 2 * i * i;
    }
    dfs_cake(max_r, max_h, M, 0, 0);
    if (min_area == MAX_VALUE)
        printf("0\n");
    else printf("%d\n", min_area);
    return 1;
}

#endif