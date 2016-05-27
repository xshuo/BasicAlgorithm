#ifdef __2388_MERGE_SORT__
#include <string.h>

//merge sort -->O(nlgn)

//merge sort need a temp array for merge.
#define N 10000
int temp_merge_array[N];


//merge也很像打牌的时候，想象如果有两叠有序的牌，要合并
//那么做法就是每次拿出最上面两叠里面最小的，直到某一叠拿完，然后
//再把剩余的那堆加进来。
void merge(int* array, int p, int q, int r) {
    //[p, q] [q+1, r]
    memset(temp_merge_array, 0, sizeof(temp_merge_array));
    int i, j, k;
    for (i = p, j = q + 1, k = 0; i <= q && j <= r; ++k) {
        if (array[i] <= array[j]) {
            temp_merge_array[k] = array[i];
            i++;
        } else {
            temp_merge_array[k] = array[j];
            j++;
        }
    }
    
    if (i > q) {
        while (j <= r) {
            temp_merge_array[k++] = array[j++];
        }
    } else {
        while (i <= q) {
            temp_merge_array[k++] = array[i++];
        }
    }
    
    memcpy(array + p, temp_merge_array, (r - p + 1) * sizeof(int));
}

void merge_sort(int* array, int start, int end) {
    if (end - start > 1) {
        merge_sort(array, start, (start + end) / 2);
        merge_sort(array, (start + end) / 2, end);
        merge(array, start, (start + end) / 2 - 1, end - 1);
    }
}
#endif