//quick sort -->O(nlgn)

//һ���quick sort������Ҳ�ᵽO(n^2)
//�����Ӱ����Ҫ����partition��λ�ã����ÿ�ηֿ�������
//ĳһ��ֻ��һ�����֣��Ǿ���bad luck
//Ϊ��ƽ��ָ��С��-->�������������
//��randomѡһ��key��Ȼ������key��������ʼλ�ã������key��
//�ָ�����
//������������������������O(nlgn)

//partition��ʱ���м���
//����Ҫ�������� �趨һ��key��Ȼ��Ѵ������key�������ƶ��������ұ�
//С�����key�������ƶ����������

//��˵�㷨�����ϵ�����

/*
��i����¼���һ��С�ڵ���key��λ�ã�Ȼ����j����loop

��ʼֵ
keyȡ��һ����iȡkey��λ�ã�jȡ�ڶ���

ѭ����ʱ�����array[j] > key����ôj++
���array[j] < key����i++���ҽ���array[i],array[j]

*/

/*
�Ƚ��������ķ�ʽ
��ʵ�ƶ�����Ҫһ���ն�
ȡ��һ��Ϊkey
��ô��һ���Ϳ���

�Ӻ���ǰ�ұ�keyС�ģ��ҵ����������Ͽն���
Ȼ�������keyС�ľ��ֿ��ˣ�Ȼ���ǰ�����ұ�key��ķŵ��ն�
ֱ��ײ�ϡ�
*/
#ifdef __2388_Q_SORT__
int q_sort_partition(int* array , int start, int end) {
    int value = array[start];
    int i, j;
    for (i = start, j = end - 1; i < j; ) {
        while (array[j] >= value && i < j) {
            j--;
        }
        array[i] = array[j];
        while (array[i] <= value && i < j) {
            i++;
        }
        array[j] = array[i];        
    }
    array[i] = value;
    return i;
}

void q_sort(int* array, int start, int end) {
     if (end - start > 1) {
         int middle = q_sort_partition(array, start, end);
         q_sort(array, start, middle);
         q_sort(array, middle + 1, end);
     }
}
#endif