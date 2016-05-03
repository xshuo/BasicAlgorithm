//#define __3009_DFS__
#ifdef __3009_BFS__
#include <iostream>

#define N 21
typedef struct Node{
    int x, y;
    int s;
    int board[N][N];
    bool operator==(Node& a) const {
        if (x == a.x && y == a.y)
            return true;
        else return false;
    }
}Node;

int W, H;
int ret;
#define START 2
#define END 3
int success;
int next[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

#define SIZE_Q 20000
Node q[SIZE_Q];
int qhead, qtail, qsize;

void bfs(Node start, Node end) {
    qhead = qtail = qsize = 0;
    q[qtail++] = start;
    qsize++;
    while (qsize) {
        Node c = q[qhead++ % SIZE_Q];
        qsize--;
        if (success == END)
            break;
        if (c.s > 10) 
            break;
        Node next_node;
        for (int i = 0; i < 4; i++) {
            int n_x = c.x, n_y = c.y;
            int step = 0;
            while (1) {
                n_x += next[i][0];
                n_y += next[i][1];
                step++;
                if (n_x < 1 || n_x > H || n_y < 1 || n_y > W || c.board[n_x][n_y]) {
                    break;
                }
            }
            if (n_x == end.x && n_y == end.y) {
                success = END;
                ret = c.s + 1;
                break;
            }
            if (n_x < 1 || n_x > H || n_y < 1 || n_y > W || step == 1)
                continue;
            else {
                next_node.x = n_x - next[i][0];
                next_node.y = n_y - next[i][1];
                memcpy(next_node.board, c.board, sizeof(c.board));
                next_node.board[n_x][n_y] = 0;
                next_node.s = c.s + 1;
                q[qtail++ % SIZE_Q] = next_node;
                qsize++;
            }
        }
    }
}

int main(int argc, char** args) {
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    while (scanf("%d%d", &W, &H)) {
        if (W == 0 || H == 0)
            break;
        Node start, end;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                scanf("%d", &start.board[i][j]);
                if (start.board[i][j] == START) {
                    start.x = i;
                    start.y = j;
                    start.s = 0;
                    start.board[i][j] = 0;
                }
                if (start.board[i][j] == END) {
                    end.x = i;
                    end.y = j;
                }

            }
        }
        success = 0;
        ret = 0;
        bfs(start, end);
        if (success != END || ret > 10)
            ret = -1;
        printf("%d\n", ret);
    }
    return 0;
}
#elif defined __3009_DFS__
#include <iostream>
#define N 21
#define START 2
#define END 3

int W, H;
int ret;
int next[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int board[N][N];

void dfs(int sx, int sy, int step, int ex, int ey) {
    if (step > 10) 
        return;
    if (step > ret)
        return;

    for (int i = 0; i < 4; i++) {
        int n_x = sx, n_y = sy;
        int s = 0;
        while (1) {
            n_x += next[i][0];
            n_y += next[i][1];
            s++;
            if (n_x < 1 || n_x > H || n_y < 1 || n_y > W || board[n_x][n_y]) {
                break;
            }
        }
        if (n_x == ex && n_y == ey) {
            if (step + 1 < ret) {
                ret = step + 1;
            }
            continue;
        }
        if (n_x < 1 || n_x > H || n_y < 1 || n_y > W || s == 1)
            continue;
        else {
            board[n_x][n_y] = 0;
            dfs(n_x - next[i][0], n_y - next[i][1], step + 1, ex, ey);
            board[n_x][n_y] = 1;
        }        
    }
    return;
}

int main(int argc, char** args) {
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    while (scanf("%d%d", &W, &H)) {
        if (W == 0 || H == 0)
            break;
        int sx, sy, ex, ey;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                scanf("%d", &board[i][j]);
                if (board[i][j] == START) {
                    sx = i;
                    sy = j;
                    board[i][j] = 0;
                }
                if (board[i][j] == END) {
                    ex = i;
                    ey = j;
                    board[i][j] = 1;
                }

            }
        }
        ret = INT_MAX;
        dfs(sx, sy, 0, ex, ey);
        if (ret <= 10)
            printf("%d\n", ret);
        else
            printf("-1\n");
    }
    return 0;
}
#endif