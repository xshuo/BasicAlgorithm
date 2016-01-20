#ifndef BST_H
#define BST_H

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

typedef struct BST_Node {
    Node_Data data;

	BST_Node* parent;
    BST_Node* lchild;
    BST_Node* rchild;

    int count;
}BST_Node;

extern BST_Node* BST_insert(BST_Node* tree, Node_Data* data);
extern BST_Node* BST_successor(BST_Node* tree);
extern BST_Node* BST_delete(BST_Node* tree, Node_Data* data);
extern BST_Node* BST_search(BST_Node* tree, Node_Data* key);
extern void BST_free_all(BST_Node* tree);

extern int get_total_count();
extern void inorder_traverse(BST_Node* tree, void (*func)(BST_Node* node));
extern void inorder_traverse_log(BST_Node* tree);
#endif