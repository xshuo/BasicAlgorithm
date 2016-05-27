#ifdef __1887__
#include <iostream>

#define MAX_N 40001

int num[MAX_N];
//int len[MAX_N];
int tail_table[MAX_N];

//nlogn, �ؼ����Ƕ�ģ�ͱ���ķ������������DP��

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
    int n, count, cas = 1;
    while (1) {
        count = 1;
        scanf("%d", &n);
        if (n == -1)
            break;
        num[0] = n;
        while (scanf("%d", &n)) {
            if (n == -1)
                break;
            num[count++] = n;
        }
        for (int i = 0, j = count - 1; i < j; i++, j--) {
            int temp = num[i];
            num[i] = num[j];
            num[j] = temp;
        }
        printf("Test #%d:\n  maximum possible interceptions: %d\n\n", cas++, LIS(num, count));
    }
    return 0;
}
#endif