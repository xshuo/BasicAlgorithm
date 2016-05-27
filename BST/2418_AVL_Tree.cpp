#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://www.geeksforgeeks.org/avl-tree-set-1-insertion/

//AVL Tree是用左右两个子树的高度差来判断当前这个树是不是平衡的
//高度差=2一定就是非平衡了
//像类似高度差为1的就是当前一个有左子树，没有右子树

//概念：平衡因子 BF(x) = |height(x->lchild) - height(x-rchild)|
//BF(x) >= 2 的时候树就不平衡了。

//插入或者删除的时候之所以会导致非平衡树的出现


//插入
//4种情况，为什么是4种情况

/*
这是不平衡的根源
两类
一类
从0 - (-1) 变成
1 - (-1) = 2

//这个旋转得找到一个比较好的思路来思考
//对于一个节点来讲，发生不平衡--》
//LL可以这样想，分自己有没有右孩子
//如果没有右孩子，那就在左孩子下插入一个，就会不平衡

//如果有右孩子，那在左孩子的左孩子下，插入一个，也会不平衡 LL
//

        A    A   
       /    /
      B    B       B        单旋转
          /       / \
         D       D   A



         A    A               E
        /    /               / \                       双旋转
       B    B               B   A
             \
              E




      A      A             C
       \      \           / \       单旋转
        C      C         A   G
                \
                 G
    
      A      A
       \      \
        C      C                                       双旋转
              /
             F
    另外一类
    从1 - (0) 变成 2 - (0)
        A           A               B
       / \        /   \           /   \
      B   C      B     C         D     A        RR_Rotate
     / \        / \             /     /  \ 
    D   E      D   E           H     E    C  
              /
             H


        A                    A                C
       / \                  / \              / \
      B   C                B   C            A   G
         / \                  / \          / \   \    LL_Rotate
         F  G                F   G        B   F   H
                                  \                
                                   H
*/


//举例，无论是插入到了左孩子的左节点的左边还是右边，
//->插入到了x->
#define AVL_TREE_CPP
#ifdef AVL_TREE_CPP
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "AVL.h"

static int total_count = 0;

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
    pivot->parent = tree->parent;
	tree->parent = pivot;

	tree->height = max(height(tree->lchild), height(tree->rchild)) + 1;
	pivot->height = max(height(pivot->lchild), height(pivot->rchild)) + 1;

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
    pivot->parent = tree->parent;
	tree->parent = pivot;
	
	tree->height = max(height(tree->lchild), height(tree->rchild)) + 1;
	pivot->height = max(height(pivot->lchild), height(pivot->rchild)) + 1;

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

AVL_Node* AVL_node_insert(AVL_Node* tree, Node_Data* data) {
    //思路，插入一棵树，返回顶点，但是顶点其实是未知的。
	if (tree == NULL) {
        tree = create_node(data);
        total_count++;
        return tree;
    } 
    if (*data > tree->data) {
        tree->rchild = AVL_node_insert(tree->rchild, data);
		tree->rchild->parent = tree;
    } else if (*data == tree->data) {
        tree->count++;
        total_count++;
		return tree;//review, will not change the height.
    } else {
        tree->lchild = AVL_node_insert(tree->lchild, data);
		tree->lchild->parent = tree;
    }

	tree->height = max(height(tree->lchild), height(tree->rchild)) + 1;

	int balance = height(tree->lchild) - height(tree->rchild);
	//only do rotate for balance once. we can review the code and add a flag for indication.
	
	if (balance > 1) {
		if (*data < tree->lchild->data) {
			//LL
			tree = right_rotate(tree);

		} else {
            //LR
            tree->lchild = left_rotate(tree->lchild);
            tree = right_rotate(tree);
		}
	} else if (balance < -1) {
        if (*data > tree->rchild->data) {
            //RR
		    tree = left_rotate(tree);
        } else {
	        //RL
		    tree->rchild = right_rotate(tree->rchild);
		    tree = left_rotate(tree);
        }
	}
    return tree;
}

AVL_Node* AVL_node_delete(AVL_Node* tree, Node_Data* data) {
    //删除这件事情，如果成功，返回新树的跟节，如果失败即找不到，其实就是什么都不做。
    //刚开始想错了，以为不能用递归
    //因为当左右子树都有的时候，后续不可能跑到外面去
    //删除的时候也只有当左右子树都有的时候，才需要求后续
    //后续一定是右子树里面最左边的那个，所以后续一定没有左子树。
    if (tree == NULL)
        return NULL;//这里一般就是找到叶子节点的左右子树了。

	if (*data < tree->data) {
        if (tree->lchild == NULL)//在树中找不到这样的节点
            return tree;
        tree->lchild->parent = NULL;//先断掉parent
		tree->lchild = AVL_node_delete(tree->lchild, data);
        if (tree->lchild != NULL)
            tree->lchild->parent = tree;//接上parent
	}else if (*data > tree->data) {
        if (tree->rchild == NULL)//在树中找不到这样的节点
            return tree;
        tree->rchild->parent = NULL;
		tree->rchild = AVL_node_delete(tree->rchild, data);
        if (tree->rchild != NULL)
            tree->rchild->parent = tree;
	}else {
		//no child
		if (tree->lchild == NULL && tree->rchild == NULL) {
            free(tree);
            tree = NULL;
		} else if (tree->lchild != NULL && tree->rchild != NULL) {
            //both left right
			AVL_Node* successor = AVL_successor(tree);
			Node_Data tempData;
			memcpy(&tempData, &tree->data, sizeof(Node_Data));
			memcpy(&tree->data, &successor->data, sizeof(Node_Data));
			memcpy(&successor->data, &tempData, sizeof(Node_Data));
			
            //我猜...
            //不要这样写，这容易，导致，tree回去的时候，不是最小的不平衡树
            /*******************************************************
            if (successor->rchild != NULL) {
                successor->rchild->parent = successor->parent;
                if (successor->parent->lchild == node)
                    successor->parent->lchild = successor->rchild;
                else
                    successor->parent->rchild = successor->rchild;
            }
            *******************************************************/
            //去删后续
            tree->rchild = AVL_node_delete(tree->rchild, data);
        } else {
            AVL_Node* temp = tree->lchild ? tree->lchild : tree->rchild;
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

	if (tree) {
		tree->height = max(height(tree->rchild), height(tree->lchild)) + 1;
		int balance = height(tree->lchild) - height(tree->rchild);

		if (balance > 1) {
			int left_balance = height(tree->lchild->lchild) - height(tree->lchild->rchild);				
			if (left_balance >= 0) {
				//LL
				tree = right_rotate(tree);
			} else {
				//LR
				tree->lchild = left_rotate(tree->lchild);
				tree = right_rotate(tree);
			}
		} else if (balance < -1) {
			int right_balance = height(tree->rchild->lchild) - height(tree->rchild->rchild);				
			if (right_balance >= 0) {
                //RL
				tree->rchild = right_rotate(tree->rchild);
				tree = left_rotate(tree);
			} else {
                //RR
                tree = left_rotate(tree);
			}
		}
	}
	return tree;
    //这个删除有点难写
}

//next larger.
AVL_Node* AVL_successor(AVL_Node* tree) {
	if (tree->rchild != NULL) {
		tree = tree->rchild;
		while(tree->lchild != NULL)
			tree = tree->lchild;
		return tree;
	} else {
		AVL_Node* p = tree->parent;
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

void postorder_free(AVL_Node* node) {
	if (node) {
		postorder_free(node->lchild);
		postorder_free(node->rchild);
		free(node);
	}
}

int get_node_count() {
	return total_count;
}
#endif