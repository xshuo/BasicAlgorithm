#ifdef __2488__
#include <iostream>

#define N 30
int n, p, q;
int board[N][N];
int path[N * N][2];
bool success;

int next[8][2] = {{-2, -1},{-2, 1},{-1, -2},{-1, 2},{1, -2},{1, 2},{2, -1},{2, 1}};

void print(int n) {
    for (int i = 1; i <= n; i++) {
        printf("%c", path[i][0] + ('A' - 1));
        printf("%d", path[i][1]);
    }
    printf("\n");
}

void dfs_path(int x, int y, int cnt) {
    if (success) return;

    for (int i = 0; i < 8; i++) {
        int next_x = x + next[i][0];
        int next_y = y + next[i][1];
        if (1 <= next_x && next_x <= q && 1 <= next_y && next_y <= p &&
            !board[next_x][next_y]) {
            board[next_x][next_y] = 1;
            path[cnt][0] = next_x;
            path[cnt][1] = next_y;
            if (cnt == q * p) {
                print(q * p);
                success = true;
                return;
            }
            dfs_path(next_x, next_y, cnt + 1);
            board[next_x][next_y] = 0;
        }
    }
}

int main(int argc, char** args) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p, &q);
        memset(board, 0, sizeof(board));
        memset(path, 0, sizeof(path));
        success = false;
        printf("Scenario #%d:\n", i);
        if (p * q == 1) {
            printf("A1\n\n");
            continue;
        }
        path[1][0] = 1;
        path[1][1] = 1;
        board[1][1] = 1;
        dfs_path(1, 1, 2);
        if (!success)
            printf("impossible\n");
        printf("\n");
    }
    return 0;
}
#endif