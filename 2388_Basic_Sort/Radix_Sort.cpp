//算法导论上的
//O(n) 这个是IBM创始人在很久之前发明的，排列卡片的
//要用到counting sort
//算法导论 99.
//线性排序
#define RADIX_SORT
#ifdef RADIX_SORT

#include <math.h>
#include <string.h>
#include <stdlib.h>
#define N 10000
int temp_counting_array[N];

int count[10];

//这里必须从右到左分拆数的每一位，所以需要提前确定数的大小范围。
#define MAX_NUM_DIGIT 7
//100 0000

//digit 表示倒数第几位
void digit_count_sort(int* array, int start, int end, int digit) {
    memset(count, 0, sizeof(count));
    memset(temp_counting_array, 0, sizeof(temp_counting_array));

    for (int i = start; i < end; ++i) {
        int num = array[i] / (int)pow(10.0, digit - 1) % 10;
        ++count[num];
    }
    //count[i] 记录小于等于i的数的数目
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i-1];
    }

    for (int i = end -1; i >= start; --i) {
        int num = array[i] / (int)pow(10.0, digit - 1) % 10;
        int index = count[num] - 1; //从数组从0开始存
        temp_counting_array[index] = array[i];
        --count[num];
    }

    memcpy(array, temp_counting_array, (end - start) * sizeof(int));
}

void radix_sort(int* array, int start, int end) {
    for (int j = 1; j <= MAX_NUM_DIGIT; ++j) {
        digit_count_sort(array, start, end, j);
    }
}

#endif