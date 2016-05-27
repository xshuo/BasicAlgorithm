//quick sort -->O(nlgn)

//一般的quick sort的最坏情况也会到O(n^2)
//这里的影响主要在于partition的位置，如果每次分开的两段
//某一段只有一个数字，那就是bad luck
//为了平衡分割大小，-->随机化快速排序
//先random选一个key，然后把这个key交换到开始位置，以这个key来
//分割数组
//这样几乎可以做到都趋向于O(nlgn)

//partition的时候有技巧
//这里要做到的是 设定一个key，然后把大于这个key的数都移动到他的右边
//小于这个key的数都移动到他的左边

//先说算法导论上的做法

/*
用i来记录最后一个小于等于key的位置，然后用j来做loop

初始值
key取第一个，i取key的位置，j取第二个

循环的时候如果array[j] > key，那么j++
如果array[j] < key，则i++，且交换array[i],array[j]

*/

/*
比较容易理解的方式
其实移动就需要一个空洞
取第一个为key
那么第一个就空了

从后往前找比key小的，找到后把这个填上空洞；
然后这个比key小的就又空了，然后从前往后找比key大的放到空洞
直到撞上。
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