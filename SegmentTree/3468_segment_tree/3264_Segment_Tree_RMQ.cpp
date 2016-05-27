//#define __RMQ__
#ifdef __RMQ__
#include <stdio.h>
#include <string.h>

#define L(x) ((x)<<1)
#define R(x) ((x)<<1 | 1)
#define MID(x) ((x)>>1)

#define N 1000001

typedef struct Node {
    int l, r;//[l,r]
    int max, min;
}Node;

int values[N];
Node s_tree[4 * N];

int min_save[N];
int max_save[N];

static inline int MAX(int a, int b) {
    return a > b ? a : b;
}

static inline int MIN(int a, int b) {
    return a < b ? a : b;
}

static inline void pushUp(int node) {
    s_tree[node].min = MIN(s_tree[L(node)].min, s_tree[R(node)].min);
    s_tree[node].max = MAX(s_tree[L(node)].max, s_tree[R(node)].max);
}

void build(int node, int left, int right) {
    s_tree[node].l = left;
    s_tree[node].r = right;

    if (left == right) {
        s_tree[node].max = s_tree[node].min = values[left];
        return;
    }
    build(L(node), left, MID(left + right));
    build(R(node), MID(left + right) + 1, right);

    pushUp(node);
}

void query(int node, int left, int right, int* min, int* max) {
    if (left == s_tree[node].l && s_tree[node].r == right) {
        *min = MIN(s_tree[node].min, *min);
        *max = MAX(s_tree[node].max, *max);
        return;
    }

    //pushDown
    int mid = MID(s_tree[node].l + s_tree[node].r);
    if (right <= mid) {
        query(L(node), left, right, min, max);
    } else if (left > mid) {
        query(R(node), left, right, min, max);
    } else {
        query(L(node), left, mid, min, max);
        query(R(node), mid + 1, right, min, max);
    }
}

int main(int argc, char** argv) {
    int m, n;

    freopen("F:\\Workplace\\POJ\\input.txt", "r", stdin);

    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", values + i);
    }
    build(1, 1, m);

    for (int i = 1; i <= m - n + 1; ++i) {
        int min = 0x7fffffff;
        int max = 0 - min;
        query(1, i, i + n - 1 , &min, &max);
        min_save[i] = min;
        max_save[i] = max;
    }

    for (int i = 1; i <= m - n + 1; ++i) {
        printf("%d ", min_save[i]);
    }

    printf("\n");

    for (int i = 1; i <= m - n + 1; ++i) {
        printf("%d ", max_save[i]);
    }
}
#endif