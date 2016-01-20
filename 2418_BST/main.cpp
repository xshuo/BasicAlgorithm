#define MAIN_CPP
#ifdef MAIN_CPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVL.h"
#include "Splay_Tree.h"

BST_Node* BST_Tree;
AVL_Node* AVL_Tree;
BST_Node* Splay_Tree;


void print_log(AVL_Node* node) {
	printf("%s\n", node->data.word);
}

void print(AVL_Node* node) {
	printf("%s %.4f\n", node->data.word, node->count * 1.0 / get_node_count() * 100);
}

void print_splay_tree(BST_Node* node) {
	printf("%s %.4f\n", node->data.word, node->count * 1.0 / get_node_count() * 100);
}

void test_splay_tree() {
    char word[30];
    Node_Data data;

    //a b c d e f g
    while (gets(word) != NULL) {
        strcpy(data.word, word);
        Splay_Tree = splay_tree_insert(Splay_Tree, &data);
    }
}

void test_avl() {
    char word[30];
    Node_Data data;

    //a b e f c d
    while (gets(word) != NULL) {
        strcpy(data.word, word);
        AVL_Tree = AVL_node_insert(AVL_Tree, &data);
    }
    inorder_traverse(AVL_Tree, print);


    strcpy(data.word, "e");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    strcpy(data.word, "f");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    strcpy(data.word, "b");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    strcpy(data.word, "a");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    strcpy(data.word, "a");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    strcpy(data.word, "d");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    strcpy(data.word, "c");
    AVL_Tree = AVL_node_delete(AVL_Tree, &data);

    postorder_free(AVL_Tree);
}


int main(int argc, char** argv) {
    freopen("F:\\Workplace\\POJ\\input.txt", "r", stdin);
    //test_avl();
    test_splay_tree();
	return 0;
}
#endif
