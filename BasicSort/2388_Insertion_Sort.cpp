//Insertion Sort O(n^2)
/*��������Ƚ����ƴ��Ƶ�ʱ��һ��һ�ŵĽ������������Ʋ��뵽֮ǰ���ź����ϵ������
����һ��������˵����Ҫ��һ�����ն�������ƽ�ƣ�һ��Ͱѵ�ǰҪ���������������Ƽ�������
����λ����Ϊ��һ���ն���Ȼ����ǰ�Ƚϣ�ǰ�����������κ��ơ�
��ʼ״̬����һ����һ��������ġ��ӵڶ�����ʼ������
*/
#ifdef __2388_INSERTION_SORT__
void insertion_sort(int* array, int start, int end) {
    int j = start + 1;
    while (j < end) {
        int i;
        int key = array[j];
        for (i = j - 1; i >= start; i--) {
            if (array[i] > key) {
                array[i + 1] = array[i];
            } else {
                array[i + 1] = key;
                break;
            }
        }
        if (i < start) 
            array[start] = key;
        j++;
    }   
}
#endif