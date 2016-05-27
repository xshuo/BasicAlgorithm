#ifdef __2533__
#include <iostream>

#define MAX_N 1001

int len[MAX_N];
int num[MAX_N];

int LIS(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        len[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && len[j] + 1> len[i]) {
                    len[i] = len[j] + 1;
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < size; i++) {
        if (len[i] > ret)
            ret = len[i];
    }
    return ret;
}

int main(int argc, char** args) {
    int n;
    scanf("%d", &n);
    for (int j = 0; j < n; j++) {
        scanf("%d", num + j);
    }
    printf("%d\n", LIS(num, n));
    return 0;
}
#endif