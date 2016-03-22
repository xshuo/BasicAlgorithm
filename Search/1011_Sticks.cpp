//#define _1011_STICKS__
#ifdef _1011_STICKS__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <functional>
#define MAX_STICKS 65

int sticks_cnt;
int sticks[MAX_STICKS];
int sticks_flag[MAX_STICKS];

bool success;
int stick_length;

void dfs_sticks(int cnt, int length, int per_stick_index, int start) {
    if (cnt == 0) {
        if (length == 0)
            success = true;        
        return;
    }
    if (success)
        return;
    if (length == 0) {
        dfs_sticks(cnt, stick_length, 0, 1);
        return;
    }

    for (int i = start; i <= sticks_cnt && !success; i++) {
        if (sticks_flag[i] == 1 || sticks[i] > length)
            continue;
        sticks_flag[i] = 1;
        per_stick_index++;
        dfs_sticks(cnt - 1, length - sticks[i], per_stick_index, i + 1);
        sticks_flag[i] = 0;

        if (per_stick_index == 1) break;
        per_stick_index--;

        while (sticks[i + 1] == sticks[i]) i++;
    }
}

int main(int argc, char** args) {
    int i;
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    while (scanf("%d", &sticks_cnt)) {
        if (sticks_cnt == 0)
            break;
        success =false;
        memset(sticks_flag, 0, sizeof(sticks_flag));
        memset(sticks, 0, sizeof(sticks));

        int sum = 0;
        int per_max_stick = 0;
        int max_stick = 0;
        for (i = 1; i <= sticks_cnt; i++) {
            scanf("%d", sticks + i);
            sum += sticks[i];
        }
        std::sort(sticks + 1, sticks + sticks_cnt + 1, std::greater<int>());
        per_max_stick = sticks[1];
        max_stick = sum / 2;

        for (int i = per_max_stick; i <= max_stick; i++) {
            if (sum % i != 0)
                continue;
            stick_length = i;
            dfs_sticks(sticks_cnt, stick_length, 0, 1);
            if (success)
                break;
        }
        if (!success)
            stick_length = sum;
        printf("%d\n", stick_length);
    }
}
#endif