
//#define MAIN_TEMP_CPP
#if defined MAIN_TEMP_CPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node_Data {
#define DATA_SIZE 30

    char word[DATA_SIZE];

    bool operator< (Node_Data &b){
        return strcmp(word, b.word) < 0;
    }
    bool operator> (Node_Data &b){
        return strcmp(word, b.word) > 0;
    }
    bool operator== (Node_Data &b){
        return strcmp(word, b.word) == 0;
    }
}Node_Data;

typedef struct AVL_Node {
    Node_Data data;

	AVL_Node* parent;
    AVL_Node* lchild;
    AVL_Node* rchild;

	int height;
    int count;
}AVL_Node;

AVL_Node* AVL_Tree;
int total_count = 0;

static AVL_Node* right_rotate(AVL_Node* tree);
static AVL_Node* left_rotate(AVL_Node* tree);

static AVL_Node* create_node(Node_Data* data) {
    AVL_Node* node = (AVL_Node*)malloc(sizeof(AVL_Node));
    memcpy(&node->data, data, sizeof(Node_Data));
    node->count = 1;
    
	node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;

	node->height = 0;//wiki
    return node;
}

static inline int height(AVL_Node* tree) {
	if (tree == NULL)
		return -1;
	else {
		return tree->height;
	}
}

static inline int max(int x, int y) {
	return x > y ? x : y;
}

void AVL_insert(AVL_Node* &tree, Node_Data* data) {
	if (tree == NULL) {
        tree = create_node(data);
        total_count++;
        return;
    } 
    if (*data > tree->data) {
        AVL_insert(tree->rchild, data);
		if (tree->rchild->parent == NULL)
			tree->rchild->parent = tree;
    } else if (*data == tree->data) {
        tree->count++;
        total_count++;
    } else {
        AVL_insert(tree->lchild, data);
		if (tree->lchild->parent == NULL)
			tree->lchild->parent = tree;
    }

	tree->height = max(height(tree->lchild), height(tree->rchild)) + 1;

	int balance = height(tree->lchild) - height(tree->rchild);
	
	
	if (balance > 1 && *data < tree->lchild->data) {
		//LL
		tree = right_rotate(tree);
	} else if (balance > 1 && *data > tree->lchild->data) {
	    //LR
		tree->lchild = left_rotate(tree->lchild);
		tree = right_rotate(tree);
	} else if (balance < -1 && *data > tree->rchild->data) {
	    //RR
		tree = left_rotate(tree);		
	} else if (balance < -1 && *data < tree->rchild->data) {
	    //RL
		tree->rchild = right_rotate(tree->rchild);
		tree = left_rotate(tree);
	}
}

/*
        A           A               B
       / \        /   \           /   \
      B   C      B     C         D     A        LL - right-rotate
     / \        / \             /     /  \ 
    D   E      D   E           H     E    C  
              /
             H
*/
static AVL_Node* right_rotate(AVL_Node* tree) {
	AVL_Node* pivot = tree->lchild;

	if (pivot->rchild != NULL)
		pivot->rchild->parent = tree;
	tree->lchild = pivot->rchild;

	pivot->rchild = tree;
	tree->parent = pivot;

	tree->height = max(height(tree->lchild), height(tree->rchild)) + 1;
	pivot->height = max(height(pivot->lchild), height(tree->rchild)) + 1;

	return pivot;
}

/*
        A                    A                C
       / \                  / \              / \
      B   C                B   C            A   G
         / \                  / \          / \   \    RR - left-rotate
         F  G                F   G        B   F   H
                                  \                
                                   H
*/

static AVL_Node* left_rotate(AVL_Node* tree) {
	AVL_Node* pivot = tree->rchild;

	tree->rchild = pivot->lchild;
	if (pivot->lchild != NULL)
		pivot->lchild->parent = tree;

	pivot->lchild = tree;
	tree->parent = pivot;
	
	tree->height = max(height(tree->lchild), height(tree->rchild)) + 1;
	pivot->height = max(height(pivot->lchild), height(tree->rchild)) + 1;

	return pivot;
}

/*
        A           A               A
       / \        /   \           /   \
      B   C      B     C         E     C   LR --> left-rotate, right-rotate
     / \        / \             /
    D   E      D   E           B 
                  /           / \
                 F           D   F
*/

/*RL --> right-rotate, left-rotate*/

void inorder_traverse(AVL_Node* node, void (*func)(AVL_Node* node)) {
	if (func == NULL) return;
    if (node) {
        inorder_traverse(node->lchild, func);
		func(node);
        inorder_traverse(node->rchild, func);
    }
}

void preorder_traverse(AVL_Node* node, void (*func)(AVL_Node* node)) {
	if (func == NULL) return;
    if (node) {
		func(node);
        preorder_traverse(node->lchild, func);
        preorder_traverse(node->rchild, func);
    }
}

void print_log(AVL_Node* node) {
	printf("%s\n", node->data.word);
}

void print(AVL_Node* node) {
	printf("%s %.4f\n", node->data.word, node->count * 1.0 / total_count * 100);
}

int main(int argc, char** argv) {
    freopen("F:\\Workplace\\POJ\\input.txt", "r", stdin);
    char word[30];
    Node_Data data;

    while (gets(word) != NULL) {
        strcpy(data.word, word);
		AVL_insert(AVL_Tree, &data);
    }
	//preorder_traverse(AVL_Tree, print_log);
	inorder_traverse(AVL_Tree, print);
	return 0;
}
#endif