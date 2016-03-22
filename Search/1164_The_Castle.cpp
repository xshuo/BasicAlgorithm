#ifdef __1164_THE_CASTLE__

#include <stdio.h>
#include <string.h>

#define N 50

int castle[N][N];
bool visit[N][N];

int m, n;
int rooms = 0;
int max_room_size = 0;

#define HAVE_NORTH_WALL(x) (x & 0x00000002)
#define HAVE_SOUTH_WALL(x) (x & 0x00000008)
#define HAVE_WEST_WALL(x)  (x & 0x00000001)
#define HAVE_EAST_WALL(x)  (x & 0x00000004)

int find_room(int i, int j) {
    int size = 0;
    if (i < 0 || j < 0 || i >= m || j >= n)
        return 0;
    if (visit[i][j] == true)
        return 0;
    visit[i][j] = true;
    if (castle[i][j] == 15)
        return 1;
    size = 1;
    if (!HAVE_NORTH_WALL(castle[i][j])) {
        size += find_room(i - 1, j);
    } 
    if (!HAVE_SOUTH_WALL(castle[i][j])) {
        size += find_room(i + 1, j);
    }
    if (!HAVE_WEST_WALL(castle[i][j])) {
        size += find_room(i, j - 1);
    }
    if (!HAVE_EAST_WALL(castle[i][j])) {
        size += find_room(i, j + 1);
    }
    return size;
}

int main_1164(int argc, char** args) {
    int i, j;
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    scanf("%d%d", &m, &n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &castle[i][j]);
        }
    }
    memset(visit, 0, sizeof(visit));
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++) {
            int room_size = find_room(i, j);
            if (room_size != 0)
                rooms++;
            if (room_size > max_room_size)
                max_room_size = room_size;            
        }
    }
    printf("%d\n%d\n", rooms, max_room_size);
    return 0;
}

#endif