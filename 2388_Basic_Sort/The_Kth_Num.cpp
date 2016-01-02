#define THE_KTH_NUM

#ifdef THE_KTH_NUM
void swap(int* x, int* y) {
    if (x == y) return;//С��zhuangB������...
    (*x) ^= (*y) ^= (*x) ^= (*y);
}

int find_k_num(int* array, int start, int end, int k) {
    if (end - start == 1)
        return array[start];
    if (k < start || k >= end) {
        return 0xffffffff;
    }

    //partition_key --> start;
    //���������������������Ҷ�����ÿ��random���ĵ�ʱ�仹��...
    int i, j;
    for (i = start, j = start + 1; j < end; j++) {
        if (array[j] < array[start]) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[start], &array[i]);

    if (k == i)
        return array[i];
    else if (k < i)
        return find_k_num(array, start, i, k);
    else
        return find_k_num(array, i + 1, end, k);
}
#endif