#define SPLAY_TREE
#ifdef SPLAY_TREE

//splay tree: http://courses.cs.washington.edu/courses/cse326/01au/lectures/SplayTrees.ppt
//http://digital.cs.usu.edu/~allan/DS/Notes/Ch22.pdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Splay_Tree.h"

static BST_Node* create_node(Node_Data* data) {
    BST_Node* node = (BST_Node*)malloc(sizeof(BST_Node));
    if (data != NULL) {
        memcpy(&node->data, data, sizeof(Node_Data));
        node->count = 1;
    }
    
	node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

static BST_Node* right_rotate(BST_Node* tree) {
    BST_Node* pivot = tree->lchild;

    if (pivot->rchild != NULL)
        pivot->rchild->parent = tree;
    tree->lchild = pivot->rchild;

    pivot->rchild = tree;
    pivot->parent = tree->parent;
    tree->parent = pivot;

    return pivot;
}

static BST_Node* left_rotate(BST_Node* tree) {
    BST_Node* pivot = tree->rchild;

    if (pivot->lchild != NULL)
        pivot->lchild->parent = tree;
    tree->rchild = pivot->lchild;

    pivot->lchild = tree;
    pivot->parent = tree->parent;
    tree->parent = pivot;

    return pivot;
}

static BST_Node* splay(BST_Node* tree, Node_Data* key) {
    BST_Node header;
    header.lchild = NULL;
    header.rchild = NULL;

    BST_Node* left_min = &header;
    BST_Node* right_max = &header;

    if (tree == NULL)
        return NULL;

    BST_Node* parent;
    BST_Node* temp;
    while (1) {
        if (*key == tree->data) {
            break;
        } else if (*key < tree->data) {
            if (tree->lchild == NULL)
                break; 
            parent = tree;
            tree = tree->lchild;
            //情况可以合并，除了，zig-zig需要旋转一下，其他的情况都是直接右链接
            //反之也一样。
            if (*key < tree->data && tree->lchild != NULL && *key < tree->lchild->data) {
                //zig-zig
                tree = tree->lchild;
                tree->parent->lchild = NULL;
                tree->parent = NULL;
                temp = right_rotate(parent);
            } else {
                //*key == tree->data || *key > tree->data || (*key < tree->data && tree->lchild == NULL)
                //zig or zig-zag same solution.
                parent->lchild = NULL;
                tree->parent = NULL;
                temp = parent;
            }
            right_max->lchild = temp;
            temp->parent = right_max;
            right_max = temp;
        } else {
            if (tree->rchild == NULL)
                break;
            parent = tree;
            tree = tree->rchild;

            if (*key > tree->data && tree->rchild != NULL && *key > tree->rchild->data) {
                //zag-zag
                tree = tree->rchild;
                tree->parent->rchild = NULL;
                tree->parent = NULL;
                temp = left_rotate(parent);
            } else {
                parent->rchild = NULL;
                tree->parent = NULL;
                temp = parent;
            }
            left_min->rchild = temp;
            temp->parent = left_min;
            left_min = temp;
        }
    }

    left_min->rchild = tree->lchild;
    if (tree->lchild != NULL)
        tree->lchild->parent = left_min;
    right_max->lchild = tree->rchild;
    if (tree->rchild != NULL)
        tree->rchild->parent = right_max;

    //combine.
    tree->lchild = header.rchild;
    if (header.rchild != NULL)
        header.rchild->parent = tree;
    tree->rchild = header.lchild;
    if (header.lchild != NULL)
        header.lchild->parent = tree;
    return tree;
}

BST_Node* splay_tree_insert(BST_Node* tree, Node_Data* data) {
    if (tree == NULL)
        return create_node(data);

    if (data == NULL)
        return tree;

    tree = splay(tree, data);
    BST_Node* temp_node;
    if (*data == tree->data) {
        tree->count++;
    } else if (*data < tree->data) {
        temp_node = create_node(data);
        temp_node->lchild = tree->lchild;
        temp_node->parent = tree;
        tree->lchild = temp_node;
        if (temp_node->lchild != NULL)
            temp_node->lchild->parent = temp_node;
    } else {
        temp_node = create_node(data);
        temp_node->rchild = tree->rchild;
        temp_node->parent = tree;
        tree->rchild = temp_node;
        if (temp_node->rchild != NULL)
            temp_node->rchild->parent = temp_node;
    }
    return tree;
}

BST_Node* splay_tree_search(BST_Node* tree, Node_Data* data) {
    return splay(tree, data);
}

BST_Node* splay_tree_delete(BST_Node* tree, Node_Data* data) {
    BST_Node* node = splay(tree, data);
    BST_Node* ret = node;
    if (node->data == *data) {
        if (node->lchild == NULL) {
            ret = node->rchild;
            free(node);
        } else {
            node->lchild->parent = NULL;
            BST_Node* left_max = splay_tree_find_max(node->lchild);
            left_max->rchild = node->rchild;
            free(node);
            ret = left_max;
        }
    }
    return ret;
}

BST_Node* splay_tree_find_max(BST_Node* tree) {
    Node_Data max_data;
    strcpy(max_data.word, "zzzzzzzzzzzzzzz");
    BST_Node* max_node = splay(tree, &max_data);
    return max_node;
}


#endif//SPLAY_TREE