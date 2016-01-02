//�㷨�����ϵ�
//O(n) �����IBM��ʼ���ںܾ�֮ǰ�����ģ����п�Ƭ��
//Ҫ�õ�counting sort
//�㷨���� 99.
//��������
#define RADIX_SORT
#ifdef RADIX_SORT

#include <math.h>
#include <string.h>
#include <stdlib.h>
#define N 10000
int temp_counting_array[N];

int count[10];

//���������ҵ���ֲ�����ÿһλ��������Ҫ��ǰȷ�����Ĵ�С��Χ��
#define MAX_NUM_DIGIT 7
//100 0000

//digit ��ʾ�����ڼ�λ
void digit_count_sort(int* array, int start, int end, int digit) {
    memset(count, 0, sizeof(count));
    memset(temp_counting_array, 0, sizeof(temp_counting_array));

    for (int i = start; i < end; ++i) {
        int num = array[i] / (int)pow(10.0, digit - 1) % 10;
        ++count[num];
    }
    //count[i] ��¼С�ڵ���i��������Ŀ
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i-1];
    }

    for (int i = end -1; i >= start; --i) {
        int num = array[i] / (int)pow(10.0, digit - 1) % 10;
        int index = count[num] - 1; //�������0��ʼ��
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