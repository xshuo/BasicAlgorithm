//这是一个动态增加的数组，在增加的间隙要找第kth number

#include <iostream>
#include <limits>
#define __1442_TREAP__
#ifndef __1442_TREAP__
////////////复杂度太高////////////////////////
void random_kth_num(int A[], int start, int end) {
    int r = (int)(rand() % (end - start)) + start;
    int tmp = A[r];
    A[r] = A[start];
    A[start] = tmp;
}

int kth_num(int A[], int start, int end, int k) {
    if (k < start || k >= end)
        return INT_MAX;
    //random_kth_num(A, start, end);
    int value = A[start];
    int i, j;
    for (i = start, j = end -1; i < j;) {
        while (i < j && A[j] > value) {
            j--;
        }
        A[i] = A[j];
        while (i < j && A[i] < value) {
            i++;
        }
        A[j] = A[i];
    }
    A[i] = value;
    if (i == k)
        return i;
    else if (k < i) 
        return kth_num(A, start, i, k);
    else return kth_num(A, i + 1, end, k);
}
///////////////////////////////////////////

//////////////////复杂度还是太高，其实跟快排一样的//////
#define LEFT(x) (x << 1 | 1)
#define RIGHT(x) (x << 1)
#define PARENT(x) (x >> 1)

void min_heap_insert(int A[], int size, int value) {
    A[size + 1] = value;
    int i = size + 1;
    while (PARENT(i)) {
        int p = PARENT(i);
        if (A[p] > A[i]) {
            int tmp = A[p];
            A[p] = A[i];
            A[i] = tmp;
            i = p;
        } else {
            break;
        }
    }
    return;
}

int min_heap_popup(int A[], int size) {
    int ret = A[1];
    A[1] = A[size];
    int p = 1, min;
    while (1) {
        int l = LEFT(p);
        int r = RIGHT(p);
        min = p;
        if (l < size && A[l] < A[min])
            min = l;
        if (r < size && A[r] < A[min])
            min = r;
        if (min == p)
            break;
        else {
            int tmp = A[min];
            A[min] = A[p];
            A[p] = tmp;
            p = min;
        }
    }
    return ret;
}
///////////////////////////////////////
#define MAX_N 30010
int arraylist[MAX_N];

int min_heap1[MAX_N];
int hsize1;

int min_heap2[MAX_N];
int hsize2;

int main(int argc, char** args) {
    int M, N;
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++)
        scanf("%d", arraylist + i);
    int k = 1;
    int order;
    memset(min_heap1, 0, sizeof(min_heap1));
    hsize1 = 0;
    while (N--) {
        scanf("%d", &order);
        while (hsize1 < order) {
            min_heap_insert(min_heap1, hsize1, arraylist[hsize1]);
            hsize1++;
        }
        memcpy(min_heap2, min_heap1, sizeof(min_heap1));
        hsize2 = hsize1;
        int ret;
        for (int i = 0; i < k; i++) {
            ret = min_heap_popup(min_heap2, hsize2);
            hsize2--;
        }
        printf("%d\n", ret);
        k++;
    }
    return 0;
}
#endif

typedef struct TreapNode {
    int key, p;
    int size;
    TreapNode* right, *left;
    TreapNode(int _key, int _p) : key(_key), p(_p), size(1), right(NULL), left(NULL){}
}TreapNode;

#define MAX_N 30010
#define RAND_NUM (rand() % MAX_N)

TreapNode* right_rotate(TreapNode* root) {
    TreapNode* leftc = root->left;

    root->size = root->size - 1 - (leftc->left ? leftc->left->size : 0);
    leftc->size = leftc->size + 1 + (root->right ? root->right->size : 0);

    root->left = leftc->right;
    leftc->right = root;

    return leftc;
}

TreapNode* left_rotate(TreapNode* root) {
    TreapNode* rightc = root->right;

    root->size = root->size - 1 - (rightc->right ? rightc->right->size : 0);
    rightc->size = rightc->size + 1 + (root->left ? root->left->size : 0);

    root->right = rightc->left;
    rightc->left = root;

    return rightc;
}

TreapNode* treap_insert(TreapNode* root, int k) {
    if (root == NULL) {
        return new TreapNode(k, RAND_NUM);
    }
    if (k < root->key) {
        root->left = treap_insert(root->left, k);
        root->size++;
        if (root->p > root->left->p) {
            root = right_rotate(root);
        }
    } else {
        root->right = treap_insert(root->right, k);
        root->size++;
        if (root->p > root->right->p) {
            root = left_rotate(root);
        }
    }
    return root;
}

TreapNode* treap_delete(TreapNode* root, int key) {

}

TreapNode* search_index(TreapNode* root, int id) {
    if (root == NULL)
        return root;
    int root_id = root->left ? root->left->size + 1 : 1;
    if (root_id == id) {
        return root;
    } else if (root_id > id) {
        return search_index(root->left, id);
    } else {
        return search_index(root->right, id - root_id);
    }
}

int arraylist[MAX_N];
int main(int argc, char** args) {
    int M, N;
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++)
        scanf("%d", arraylist + i);
    int k = 1;
    int order;
    TreapNode* root = NULL;
    int size = 0;
    while (N--) {
        scanf("%d", &order);
        while (size < order) {
            root = treap_insert(root, arraylist[size++]);
        }
        printf("%d\n", search_index(root, k++)->key);
    }
    return 0;
}