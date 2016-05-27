//Insertion Sort O(n^2)
/*插入排序比较类似打牌的时候，一张一张的将最新摸到的牌插入到之前有排好序的系列里面
对于一个数组来说，需要有一个“空洞”来做平移，一般就把当前要“摸到”的那张牌记下来，
他的位置作为第一个空洞，然后向前比较，前面比他大的依次后移。
初始状态，第一个数一定是有序的。从第二个开始往后摸
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