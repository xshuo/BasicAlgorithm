#ifdef __CATCH_THAT_COW__
#include <iostream>
#include <queue>

using std::queue;

#define MAX_K 200001

queue<int> bfs_queue;
int d[MAX_K];
bool v[MAX_K];

int bfs_catch_cow(int start, int end) {    
    memset(d, 0, sizeof(d));
    memset(v, 0, sizeof(v));

    bfs_queue.push(start);
    d[start] = 0;
    v[start] = true;
    while (!bfs_queue.empty()) {
        int current = bfs_queue.front();
        if (current == end)
            break;
        int next = current + 1;
        if (next < MAX_K && !v[next]) {
            d[next] = d[current] + 1;
            v[next] = true;
            bfs_queue.push(next);
        }

        next = current - 1;
        if (0 <= next && next < MAX_K && !v[next]) {
            d[next] = d[current] + 1;
            v[next] = true;
            bfs_queue.push(next);
        }

        next = current << 1;
        if (next < MAX_K && !v[next]) {
            d[next] = d[current] + 1;
            v[next] = true;
            bfs_queue.push(next);
        }
        bfs_queue.pop();
    }
    return d[end];
}

int main(int argc, char** args) {
    int N, K;
    scanf("%d%d", &N, &K);
    printf("%d\n", bfs_catch_cow(N, K));
}
#endif