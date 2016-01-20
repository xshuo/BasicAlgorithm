#define BST_CPP
#ifdef BST_CPP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BST.h";
//splay tree: http://courses.cs.washington.edu/courses/cse326/01au/lectures/SplayTrees.ppt
static int total_count = 0;

static BST_Node* create_node(Node_Data* data) {
    BST_Node* node = (BST_Node*)malloc(sizeof(BST_Node));
    memcpy(&node->data, data, sizeof(Node_Data));
    node->count = 1;
    
	node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

static void destory_node(BST_Node* node) {
    free(node);
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

BST_Node* BST_insert(BST_Node* tree, Node_Data* data) {
    if (tree == NULL) {
        tree = create_node(data);
        total_count++;
        return tree;
    } 
    if (*data > tree->data) {
        tree->rchild = BST_insert(tree->rchild, data);
		tree->rchild->parent = tree;
    } else if (*data == tree->data) {
        tree->count++;
        total_count++;
    } else {
        tree->lchild = BST_insert(tree->lchild, data);
		tree->lchild->parent = tree;
    }
    return tree;
}

BST_Node* BST_node_delete(BST_Node* tree, Node_Data* data) {
    if (tree == NULL)
        return NULL;//这里一般就是找到叶子节点的左右子树了。

	if (*data < tree->data) {
        if (tree->lchild == NULL)//在树中找不到这样的节点
            return tree;
        tree->lchild->parent = NULL;//先断掉parent
		tree->lchild = BST_node_delete(tree->lchild, data);
        if (tree->lchild != NULL)
            tree->lchild->parent = tree;//接上parent
	}else if (*data > tree->data) {
        if (tree->rchild == NULL)//在树中找不到这样的节点
            return tree;
        tree->rchild->parent = NULL;
		tree->rchild = BST_node_delete(tree->rchild, data);
        if (tree->rchild != NULL)
            tree->rchild->parent = tree;
	}else {
		//no child
		if (tree->lchild == NULL && tree->rchild == NULL) {
            free(tree);
            tree = NULL;
		} else if (tree->lchild != NULL && tree->rchild != NULL) {
            //both left right
			BST_Node* successor = BST_successor(tree);
			Node_Data tempData;
			memcpy(&tempData, &tree->data, sizeof(Node_Data));
			memcpy(&tree->data, &successor->data, sizeof(Node_Data));
			memcpy(&successor->data, &tempData, sizeof(Node_Data));

            tree->rchild = BST_node_delete(tree->rchild, data);
        } else {
            BST_Node* temp = tree->lchild ? tree->lchild : tree->rchild;
            if (tree->parent != NULL) {
                if (tree->parent->lchild == tree) {
                    tree->parent->lchild = temp;
                } else {
                    tree->parent->rchild = temp;                
                }
                temp->parent = tree->parent;
                free(tree);
                tree = NULL;
            } else {
                temp->parent = NULL;//root;
                free(tree);
                tree = temp;
            }
		}
	}
    return tree;
}


BST_Node* BST_search(BST_Node* tree, Node_Data* key) {
    //开始没想到什么好办法，就自底向上了，
    BST_Node* ret;
    if (tree == NULL) {
        return NULL;
    }
    if (tree->data == *key) {
        return tree;
    } else if (*key < tree->data) {
        ret = BST_search(tree->lchild, key);
    } else if (*key > tree->data) {
        ret = BST_search(tree->rchild, key);
    }
    
    BST_Node** temp_parent = NULL;
    if (tree->parent != NULL) {
        if (tree->parent->lchild != NULL && tree->parent->lchild == tree)
            temp_parent = &tree->parent->lchild;
        else if (tree->parent->rchild != NULL && tree->parent->rchild == tree) 
            temp_parent = &tree->parent->rchild;
    }//需不需要往上挂，挂在什么地方。

    BST_Node* temp;
    if (tree->lchild != NULL) {
        BST_Node* lchild = tree->lchild;
        if (tree->parent == NULL && lchild->data == *key) {
            right_rotate(tree);
        } else if (lchild->lchild != NULL && lchild->lchild->data == *key) {
            temp = right_rotate(right_rotate(tree));
            if (temp_parent != NULL)
                *temp_parent = temp;
        } else if (lchild->rchild != NULL && lchild->rchild->data == *key) {
            tree->lchild = left_rotate(tree->lchild);
            temp = right_rotate(tree);
            if (temp_parent != NULL)
                *temp_parent = temp;
        }
    } else if (tree->rchild != NULL) {
        BST_Node* rchild = tree->rchild;
        if (tree->parent == NULL && rchild->data == *key) {
            left_rotate(tree);
        } else if (rchild->rchild != NULL && rchild->rchild->data == *key) {
            temp = left_rotate(left_rotate(tree));
            if (temp_parent != NULL)
                *temp_parent = temp;
        } else if (rchild->lchild != NULL && rchild->lchild->data == *key) {
            tree->rchild = right_rotate(tree->rchild);
            temp = left_rotate(tree);
            if (temp_parent != NULL)
                *temp_parent = temp;
        }
    }
    return ret;
    //这个被我写的好复杂.
}

//next larger.
BST_Node* BST_successor(BST_Node* tree) {
	if (tree->rchild != NULL) {
		tree = tree->rchild;
		while(tree->lchild != NULL)
			tree = tree->lchild;
		return tree;
	} else {
		BST_Node* p = tree->parent;
		while(p != NULL){
			if (p->lchild == tree) {
				break;
			} else {
				tree = tree->parent;
				p = tree->parent;
			}
		}
		return p;
	}
}

void inorder_traverse(BST_Node* tree, void (*func)(BST_Node* node)){    
    if (tree) {
        inorder_traverse(tree->lchild, func);
        func(tree);
        inorder_traverse(tree->rchild, func);
    }
}

void inorder_traverse_log(BST_Node* tree){
    if (tree) {
        inorder_traverse_log(tree->lchild);
        printf("%s ", tree->data.word);
        inorder_traverse_log(tree->rchild);
    }
}


void BST_free_all(BST_Node* tree) {
    if (tree) {
        BST_free_all(tree->lchild);
        BST_free_all(tree->rchild);
        free(tree);
    }
}

int get_total_count() {
    return total_count;
}
#endif

//#define CREATE_BST_WITH_GLOBAL_ARRAY
#ifdef CREATE_BST_WITH_GLOBAL_ARRAY
char words[2000000][30];
short counts[2000000];
void create_search_tree_s() {
    char word[30];
    memset(words, 0, sizeof(words));
    memset(counts, 0, sizeof(counts));

    gets(word);
    strncpy(words[1], word, strlen(word));

    total_count = 1;
    counts[1] = 1;

    while (gets(word) != NULL) {
        int i = 1;
        ++total_count;
        while (1) {
            int cmp = strcmp(word, words[i]);
            if (cmp == 0) {
                ++counts[i];
                break;
            } else if (cmp > 0) {
                i = 2 * i + 1;
            } else {
                i = 2 * i;
            }
            if (strcmp(words[i], "\0") == 0) {
                strncpy(words[i], word, strlen(word));
                counts[i] = 1;
                break;
            }
        }
    }
}

void LDR_search_tree(int i) {
    if (strcmp(words[i], "\0") == 0) {
        return;
    }
    LDR_search_tree(i * 2);
    printf("%s %.4f\n", words[i], counts[i] * 1.0 / total_count * 100);
    LDR_search_tree(i * 2 + 1);
}
#endif
