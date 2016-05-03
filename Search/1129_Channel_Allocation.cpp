#ifdef __1129__
#include <iostream>
//四色原理，这个可以按度排序后贪心，离散数学书本有讲的
//这里搜索
#define MAX_N 27
int graph[MAX_N][MAX_N];
int color[MAX_N];

int n;

bool is_safe(int index, int c) {
    for (int i = 1; i <= n; i++) {
        if (graph[i][index] && color[i] == c)
            return false;
    }
    return true;
}

bool dfs_color(int color[], int index, int m_color) {
    if (index > n) {
        //print color
        return true;
    }
    for (int i = 1; i <= m_color; i++) {
        if (is_safe(index, i)) {
            color[index] = i;
            if (dfs_color(color, index + 1, m_color) == true)
                return true;
            else color[index] = -1;
        }
    }
    return false;
}

int min_channel(int color[]) {
    for (int i = 1; i <= 3; i++) {
        if (dfs_color(color, 1, i))
            return i;
    }
    //
    return 4;
}

int main(int argc, char** args) {
    while (scanf("%d", &n)) {
        if (!n) break;

        memset(graph, 0, sizeof(graph));
        memset(graph, 0xff, sizeof(color));
        char temp[30];

        for (int j = 0; j < n; j++) {
            scanf("%s", temp);

            for (int i = 2; i < strlen(temp); i++) {
                graph[temp[0] - 'A' + 1][temp[i] - 'A' + 1] = 1;
                graph[temp[i] - 'A' + 1][temp[0] - 'A' + 1] = 1;
            }
        }
        int ret = min_channel(color);
        if (ret == 1) 
            printf("1 channel needed.\n");
        else printf("%d channels needed.\n", ret);
    }
    return 0;
}
#endif