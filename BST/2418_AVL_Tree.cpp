#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://www.geeksforgeeks.org/avl-tree-set-1-insertion/

//AVL Tree�����������������ĸ߶Ȳ����жϵ�ǰ������ǲ���ƽ���
//�߶Ȳ�=2һ�����Ƿ�ƽ����
//�����Ƹ߶Ȳ�Ϊ1�ľ��ǵ�ǰһ������������û��������

//���ƽ������ BF(x) = |height(x->lchild) - height(x-rchild)|
//BF(x) >= 2 ��ʱ�����Ͳ�ƽ���ˡ�

//�������ɾ����ʱ��֮���Իᵼ�·�ƽ�����ĳ���


//����
//4�������Ϊʲô��4�����

/*
���ǲ�ƽ��ĸ�Դ
����
һ��
��0 - (-1) ���
1 - (-1) = 2

//�����ת���ҵ�һ���ȽϺõ�˼·��˼��
//����һ���ڵ�������������ƽ��--��
//LL���������룬���Լ���û���Һ���
//���û���Һ��ӣ��Ǿ��������²���һ�����ͻ᲻ƽ��

//������Һ��ӣ��������ӵ������£�����һ����Ҳ�᲻ƽ�� LL
//

        A    A   
       /    /
      B    B       B        ����ת
          /       / \
         D       D   A



         A    A               E
        /    /               / \                       ˫��ת
       B    B               B   A
             \
              E




      A      A             C
       \      \           / \       ����ת
        C      C         A   G
                \
                 G
    
      A      A
       \      \
        C      C                                       ˫��ת
              /
             F
    ����һ��
    ��1 - (0) ��� 2 - (0)
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


//�����������ǲ��뵽�����ӵ���ڵ����߻����ұߣ�
//->���뵽��x->
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
    //˼·������һ���������ض��㣬���Ƕ�����ʵ��δ֪�ġ�
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
    //ɾ��������飬����ɹ������������ĸ��ڣ����ʧ�ܼ��Ҳ�������ʵ����ʲô��������
    //�տ�ʼ����ˣ���Ϊ�����õݹ�
    //��Ϊ�������������е�ʱ�򣬺����������ܵ�����ȥ
    //ɾ����ʱ��Ҳֻ�е������������е�ʱ�򣬲���Ҫ�����
    //����һ������������������ߵ��Ǹ������Ժ���һ��û����������
    if (tree == NULL)
        return NULL;//����һ������ҵ�Ҷ�ӽڵ�����������ˡ�

	if (*data < tree->data) {
        if (tree->lchild == NULL)//�������Ҳ��������Ľڵ�
            return tree;
        tree->lchild->parent = NULL;//�ȶϵ�parent
		tree->lchild = AVL_node_delete(tree->lchild, data);
        if (tree->lchild != NULL)
            tree->lchild->parent = tree;//����parent
	}else if (*data > tree->data) {
        if (tree->rchild == NULL)//�������Ҳ��������Ľڵ�
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
			
            //�Ҳ�...
            //��Ҫ����д�������ף����£�tree��ȥ��ʱ�򣬲�����С�Ĳ�ƽ����
            /*******************************************************
            if (successor->rchild != NULL) {
                successor->rchild->parent = successor->parent;
                if (successor->parent->lchild == node)
                    successor->parent->lchild = successor->rchild;
                else
                    successor->parent->rchild = successor->rchild;
            }
            *******************************************************/
            //ȥɾ����
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
    //���ɾ���е���д
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