#ifdef __2251__
#include <iostream>

#define MAX_Q 2000
#define N 35
int G[N][N][N];
bool visit[N][N][N];

typedef struct Point {
    int x;
    int y;
    int z;
    int s;
    Point(int _x = 0, int _y = 0, int _z = 0, int _s = 0)
        :x(_x), y(_y), z(_z), s(_s){}
    bool operator== (Point& p) const {
        if (x == p.x && y == p.y && z == p.z)
            return true;
        else return false;
    }
}Point;

int L, R, C;
int ret;

Point q[MAX_Q];
int qhead, qtail, qsize;

int next[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
void bfs(Point start, Point end) {
    qhead = qtail = qsize = 0;
    memset(visit, 0, sizeof(visit));
    q[qtail++] = start;
    visit[start.x][start.y][start.z] = true;
    qsize += 1;
    while (qsize) {
        Point c = q[qhead++ % MAX_Q];
        qsize--;
        if (c == end) {
            ret = c.s;
            break;
        }
        int n_x, n_y, n_z;
        for (int i = 0; i < 6; i++) {
            n_x = c.x + next[i][0];
            n_y = c.y + next[i][1];
            n_z = c.z + next[i][2];
            if (0 <= n_x && n_x < L &&
                0 <= n_y && n_y < R &&
                0 <= n_z && n_z < C &&
                G[n_x][n_y][n_z] &&
                !visit[n_x][n_y][n_z]) {
                q[qtail++ % MAX_Q] = Point(n_x, n_y, n_z, c.s + 1);
                qsize++;
                visit[n_x][n_y][n_z] = true;
            }
        }
    }
}

int main(int argc, char** args) {
    while(scanf("%d%d%d", &L, &R, &C)) {
        if (L == 0 && R == 0 && C == 0)
            break;
        Point s, e;
        memset(G, 0, sizeof(G));
        ret = -1;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < R; j++) {
                char str[N];
                scanf("%s", str);
                for (int k = 0; k < C; k++) {
                    if (str[k] == '.')
                        G[i][j][k] = 1;
                    else if (str[k] == '#')
                        G[i][j][k] = 0;
                    else if (str[k] == 'S') {
                        G[i][j][k] = 1;
                        s.x = i;
                        s.y = j;
                        s.z = k;
                        s.s = 0;
                    } else if (str[k] == 'E') {
                        G[i][j][k] = 1;
                        e.x = i;
                        e.y = j;
                        e.z = k;
                        e.s = 0;
                    }
                }
            }
        bfs(s, e);
        if (ret == -1)
            printf("Trapped!\n");
        else 
            printf("Escaped in %d minute(s).\n", ret);        
    }
    return 0;
}
#endif