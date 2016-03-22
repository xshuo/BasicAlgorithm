#include <iostream>
#include <queue>
#include <cmath>

using std::queue;
using std::priority_queue;

typedef struct Point {
    int x;
    int y;
    int L;

    int F;
    int G;
    int H;
    Point(int _x, int _y) : x(_x), y(_y), L(0) {}
    bool operator == (Point& p) {
        if (x == p.x && y == p.y)
            return true;
        else return false;
    }
    bool operator>= (const Point& p) const{
        return F < p.F;
    }
}Point;

#define __2243_A_STAR__
#ifndef __2243_A_STAR__
#define N 10
bool visit[N][N];
bool rvisit[N][N];

int d[N][N];
int rd[N][N];
int moves[8][2] = {{1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}};

int bfs_knight_moves(Point start, Point end) {
    queue<Point> bfs_queue;
    memset(visit, 0, sizeof(visit));
    start.L = 0;
    bfs_queue.push(start);
    visit[start.x][start.y] = true;

    while (!bfs_queue.empty()) {
        Point c = bfs_queue.front();
        if (c == end)
            break;
        for (int i = 0; i < 8; i++) {
            Point ex(c.x + moves[i][0], c.y + moves[i][1]);
            if (ex.x > 8 || ex.x <= 0 || ex.y > 8 || ex.y <= 0)
                continue;
            if (visit[ex.x][ex.y])
                continue;
            ex.L = c.L + 1;
            bfs_queue.push(ex);
            visit[ex.x][ex.y] = true;          
        }
        bfs_queue.pop();
    }
    return bfs_queue.front().L;
}

int bibfs_knight_moves(Point start, Point end) {
    queue<Point> bfs_q, rbfs_q;
    memset(visit, 0, sizeof(visit));
    memset(rvisit, 0, sizeof(rvisit));
    start.L = 0;
    bfs_q.push(start);
    visit[start.x][start.y] = true;
    d[start.x][start.y] = 0;

    end.L = 0;
    rbfs_q.push(end);
    rvisit[end.x][end.y] = true;
    rd[end.x][end.y] = 0;

    if (start == end)
        return 0;
    int ret;

    while (!bfs_q.empty() && !rbfs_q.empty()) {
        if (bfs_q.size() <= rbfs_q.size()) {
            int cL = bfs_q.front().L;
            while (1) {
                Point c = bfs_q.front();
                if (c.L != cL)//by layer.
                    break;

                for (int i = 0; i < 8; i++) {
                    Point ex(c.x + moves[i][0], c.y + moves[i][1]);
                    if (ex.x > 8 || ex.x <= 0 || ex.y > 8 || ex.y <= 0)
                        continue;
                    if (rvisit[ex.x][ex.y]) {
                        return d[c.x][c.y] + rd[ex.x][ex.y] + 1;
                    }
                    if (visit[ex.x][ex.y])
                        continue;
                    ex.L = c.L + 1;
                    d[ex.x][ex.y] = d[c.x][c.y] + 1;
                    bfs_q.push(ex);
                    visit[ex.x][ex.y] = true;
                }
                bfs_q.pop();
            }
        } else {
            int cL = rbfs_q.front().L;
            while (1) {
                Point c = rbfs_q.front();
                if (c.L != cL)//by layer.
                    break;

                for (int i = 0; i < 8; i++) {
                    Point ex(c.x + moves[i][0], c.y + moves[i][1]);
                    if (ex.x > 8 || ex.x <= 0 || ex.y > 8 || ex.y <= 0)
                        continue;
                    if (visit[ex.x][ex.y]) {
                        return rd[c.x][c.y] + d[ex.x][ex.y] + 1;
                    }
                    if (rvisit[ex.x][ex.y])
                        continue;
                    ex.L = c.L + 1;
                    rd[ex.x][ex.y] = rd[c.x][c.y] + 1;
                    rbfs_q.push(ex);
                    rvisit[ex.x][ex.y] = true;
                }
                rbfs_q.pop();
            }
        }
    }
    return -1;
}

#else
#define N 10
bool visit[N][N];
int moves[8][2] = {{1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}};

int H(Point c, Point end) {
    return 10 *(abs(c.x - end.x) + abs(c.y - end.y));
}

int astar_knight_moves(Point start, Point end) {
    priority_queue<Point> bfs_q;
    memset(visit, 0, sizeof(visit));
    start.L = 0;
    start.G = 0;
    start.H = H(start, end);
    start.F = start.G + start.H;
    bfs_q.push(start);
    visit[start.x][start.y] = true;

    while (!bfs_q.empty()) {
        Point c = bfs_q.top();
        if (c == end)
            break;
        for (int i = 0; i < 8; i++) {
            Point ex(c.x + moves[i][0], c.y + moves[i][1]);
            if (ex.x > 8 || ex.x <= 0 || ex.y > 8 || ex.y <= 0)
                continue;
            if (visit[ex.x][ex.y])
                continue;
            ex.L = c.L + 1;
            ex.G = c.G + 23;
            ex.H = H(ex, end);
            ex.F = ex.G + ex.H;
            bfs_q.push(ex);
            visit[ex.x][ex.y] = true;
        }
        bfs_q.pop();
    }
    return bfs_q.top().L;
}

#endif


int main(int argc, char** args) {
    char s[3], e[3];
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    while (scanf("%s", s) != EOF) {
        scanf("%s", e);
        int i = s[0] - 'a' + 1;
        int j = s[1] - '0';
        Point start(i, j);
        i = e[0] - 'a' + 1;
        j = e[1] - '0';
        Point end(i, j);
        //printf("To get from %s to %s takes %d knight moves.\n", s, e, bfs_knight_moves(start, end));//407ms
        //printf("To get from %s to %s takes %d knight moves.\n", s, e, bibfs_knight_moves(start, end));//172ms
        printf("To get from %s to %s takes %d knight moves.\n", s, e, astar_knight_moves(start, end));
        //printf("-----------------------------------------------------\n");
    }
}