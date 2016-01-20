#ifndef AVL_H
#define AVL_H

#include "BST.h"

typedef struct AVL_Node {
    Node_Data data;

	AVL_Node* parent;
    AVL_Node* lchild;
    AVL_Node* rchild;

	int height;
    int count;
}AVL_Node;

int get_node_count();
void preorder_traverse(AVL_Node* node, void (*func)(AVL_Node* node));
void inorder_traverse(AVL_Node* node, void (*func)(AVL_Node* node));

AVL_Node* AVL_node_insert(AVL_Node* tree, Node_Data* data);
AVL_Node* AVL_node_delete(AVL_Node* tree, Node_Data* data);
AVL_Node* AVL_successor(AVL_Node* tree);
void postorder_free(AVL_Node* node);
#endif