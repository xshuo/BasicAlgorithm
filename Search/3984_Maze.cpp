#ifdef __MAZE__
#include <iostream>
#include <queue>

using std::queue;

typedef struct Node {
    int x, y;
    int value;
    bool visit;

    int p_x, p_y;
} Node;

Node maze[5][5];

#define valid(x) (0 <= (x) && (x) <= 5)

void bfs_maze(int startx, int starty, int endx, int endy) {
    queue<Node> bfs_queue;
    maze[startx][starty].visit = true;
    maze[startx][starty].p_x = -1;
    maze[startx][starty].p_y = -1;

    bfs_queue.push(maze[startx][starty]);
    while (!bfs_queue.empty()) {
        Node c = bfs_queue.front();
        if (c.x == maze[endx][endy].x && c.y == maze[endx][endy].y)
            break;
        //up
        if (valid(c.y + 1) && 
            !maze[c.x][c.y + 1].visit &&
            !maze[c.x][c.y + 1].value) {
            maze[c.x][c.y + 1].visit = true;
            maze[c.x][c.y + 1].p_x = c.x;
            maze[c.x][c.y + 1].p_y = c.y;
            bfs_queue.push(maze[c.x][c.y + 1]);
        }
        //down
        if (valid(c.y - 1) && 
            !maze[c.x][c.y - 1].visit &&
            !maze[c.x][c.y - 1].value) {
            maze[c.x][c.y - 1].visit = true;
            maze[c.x][c.y - 1].p_x = c.x;
            maze[c.x][c.y - 1].p_y = c.y;
            bfs_queue.push(maze[c.x][c.y - 1]);
        }
        //left
        if (valid(c.x - 1) && 
            !maze[c.x - 1][c.y].visit &&
            !maze[c.x - 1][c.y].value) {
            maze[c.x - 1][c.y].visit = true;
            maze[c.x - 1][c.y].p_x = c.x;
            maze[c.x - 1][c.y].p_y = c.y;
            bfs_queue.push(maze[c.x - 1][c.y]);
        }
        //right
        if (valid(c.x + 1) && 
            !maze[c.x + 1][c.y].visit &&
            !maze[c.x + 1][c.y].value) {
            maze[c.x + 1][c.y].visit = true;
            maze[c.x + 1][c.y].p_x = c.x;
            maze[c.x + 1][c.y].p_y = c.y;
            bfs_queue.push(maze[c.x + 1][c.y]);
        }
        bfs_queue.pop();
    }
}

void print(int startx, int starty, int endx, int endy) {
    if (endx == startx && endy == starty) {
        printf("(%d, %d)\n", startx, starty);
        return;
    } else {
        print(startx, starty, maze[endx][endy].p_x, maze[endx][endy].p_y);
        printf("(%d, %d)\n", maze[endx][endy].x, maze[endx][endy].y);
    }
}

int main(int argc, char** args) {
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    int value;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &value);
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].value = value;
            maze[i][j].visit = false;
            maze[i][j].p_x = -1;
            maze[i][j].p_y = -1;
        }
    }
    bfs_maze(0, 0, 4, 4);
    print(0, 0, 4, 4);
}
#endif