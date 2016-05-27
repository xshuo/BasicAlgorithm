#ifdef __RANGE_UPDATE_SUM__
#define __LOCAL_IO__
//Range Sum & Range update
#include <stdio.h>
#include <string.h>

#define N 100001
#define L(x) (x << 1) //*2
#define R(x) (x << 1 | 1) //*2 + 1
#define MID(x) (x >> 1)// /2

int array_value[N];

typedef struct Node {
    int left, right;
    __int64 add;
    __int64 sum;
} Node;

Node s_tree[4 * N];
//int position[N];

void build(int node, int left, int right);
void update(int node, int left, int right, __int64 data);
__int64 query(int node, int left, int right);

int main(int argc, char** argv) {
    int n, q;
    int i, j;
#ifdef __LOCAL_IO__
    freopen("F:\\Workplace\\POJ\\input.txt", "r", stdin);
#endif
    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; ++i) {
        scanf("%d", array_value + i);
    }
    build(1, 1, n);
    for (i = 1; i <= q; ++i) {
        char op;
        int from, to;
        __int64 add;
        getchar();
        scanf("%c", &op);
        if (op == 'C') {
            scanf("%d %d %I64d", &from, &to, &add);
            update(1, from, to, add);
        } else {
            scanf("%d %d", &from, &to);
            printf("%I64d\n", query(1, from , to));
        }
    }
    return 0;
}


static void pushDown(int node) {
    if (s_tree[node].add != 0) {
        s_tree[L(node)].add += s_tree[node].add;
        s_tree[L(node)].sum += 
            (s_tree[L(node)].right - s_tree[L(node)].left + 1) * s_tree[node].add;

        s_tree[R(node)].add += s_tree[node].add;
        s_tree[R(node)].sum += 
            (s_tree[R(node)].right - s_tree[R(node)].left + 1) * s_tree[node].add;

        s_tree[node].add = 0;
    }
}

static void pushUp(int node) {
    s_tree[node].sum = s_tree[L(node)].sum + s_tree[R(node)].sum;
}

void build(int node, int left, int right) {
    s_tree[node].left = left;
    s_tree[node].right = right;
    s_tree[node].sum = 0;
    s_tree[node].add = 0;

    if (left == right) {
        s_tree[node].sum = array_value[left];//init value
        //position[left] = node;
        return;
    } 
    build(L(node), left, MID(left + right));
    build(R(node), MID(left + right) + 1, right);
    s_tree[node].sum = s_tree[L(node)].sum + s_tree[R(node)].sum;
    //pushUp(node);
}

void update(int node, int left, int right, __int64 data) {
    if (left <= s_tree[node].left && right >= s_tree[node].right) {
        s_tree[node].add += data;
        s_tree[node].sum += (s_tree[node].right - s_tree[node].left + 1) * data;
        return;
    }
    pushDown(node);

    s_tree[node].sum += (right - left + 1) * data;
    int mid = MID(s_tree[node].left + s_tree[node].right);

    if (right <= mid)
        update(L(node), left, right, data);
    else if (left > mid)
        update(R(node), left, right, data);
    else {
        update(L(node), left, mid, data);   
        update(R(node), mid + 1, right, data);
    }

    //pushUp(node);
}

__int64 query(int node, int left, int right) {
    if (left <= s_tree[node].left && right >= s_tree[node].right)
        return s_tree[node].sum;
    pushDown(node);

    int mid = MID(s_tree[node].left + s_tree[node].right);
    __int64 sum = 0;

    if (right <= mid)
        sum = query(L(node), left, right);
    else if (left > mid)
        sum = query(R(node), left, right);
    else {
        sum = query(L(node), left, mid) + query(R(node), mid + 1, right);
    }
    
    //pushUp(node);
    return sum;
}
#endif