#ifdef __1887__
#include <iostream>

#define MAX_N 40001

int num[MAX_N];
//int len[MAX_N];
int tail_table[MAX_N];

//nlogn, 关键还是对模型本身的分析。这个不是DP了

int b_search(int arr[], int start, int end, int k) {
    if (start == end)
        return start;
    int mid = (start + end) >> 1;
    if (arr[mid] == k)
        return -1;
    else if (arr[mid] < k)
        return b_search(arr, mid + 1, end, k);
    else return b_search(arr, start, mid, k);
}

int LIS(int arr[], int size) {
    memset(tail_table, 0xff, sizeof(tail_table));
    int max_len = 0;
    for (int i = 0; i < size; i++) {
        int loca = b_search(tail_table, 0, max_len + 1, arr[i]);
        if (loca == -1)
            continue;
        else if (loca > max_len) {
            tail_table[loca] = arr[i];
            max_len++;
        } else {
            tail_table[loca] = arr[i];
        }
    }
    return max_len;
}

int main(int argc, char** args) {
    int count, n;
    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            scanf("%d", num + j);
        }
        printf("%d\n", LIS(num, n));
    }
    return 0;
}
#endif