/*
 * File: 05binary_tree.cpp
 * Info: 二叉树
 * Date: 2022-05-20
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_OP 4

// 节点定义
typedef struct Node{
    int data;
    struct Node * lchild;
    struct Node * rchild;
} Node;
// 二叉树定义
typedef struct Tree{
    Node * root;
    int length;
} Tree;

// 初始化节点
Node * init_node(int val){
    Node * p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

// 初始化树
Tree * init_tree(){
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->length = 0; 
    return tree;
}

// 插入节点
// root是子树，返回值是插入位置
Node * insert_node(Node * root, int val, int * ret){
    if(root == NULL){
        *ret = 1;
        return init_node(val);
    }
    if(root->data > val)
        root->lchild = insert_node(root->lchild, val, ret);
    else
        root->rchild = insert_node(root->rchild, val, ret);

    return root;
}

// 插入节点到树
// 成功返回1， 失败返回0
int insert(Tree * tree, int val){
    int flag = 0;
    tree->root = insert_node(tree->root, val, &flag);
    return flag;
}

// 销毁节点
void destory_node(Node * p){
    if(p == NULL) return;
    destory_node(p->lchild);
    destory_node(p->rchild);
    free(p);
    return;
}

// 销毁树
void destory_tree(Tree * tree){
    if(tree == NULL) return;
    destory_node(tree->root);
    free(tree);
    return;
}

//  以广义表形式输出节点
void output_node(Node * p){
    if(p == NULL) return;
    printf("%d", p->data);
    if(p->lchild == NULL && p->rchild == NULL) return;
    printf("(");
    output_node(p->lchild);
    printf(", ");
    output_node(p->rchild);
    printf(")");
    return;
}

//  以广义表形式输出二叉树
void output(Tree * tree){
    if(tree == NULL) return;
    printf("tree(%d) = ", tree->length);
    output_node(tree->root);
    printf("\n");
    return;
}

// 前序遍历
void preorder_node(Node * p){
    if(p == NULL) return;
    printf("%d ", p->data);
    preorder_node(p->lchild);
    preorder_node(p->rchild);
}
void preorder(Tree * tree){
    printf("preorder: ");
    preorder_node(tree->root);
    printf("\n");
}

// 中序遍历
void inorder_node(Node * p){
    if(p == NULL) return;
    inorder_node(p->lchild);
    printf("%d ", p->data);
    inorder_node(p->rchild);
}
void inorder(Tree * tree){
    printf("inorder: ");
    inorder_node(tree->root);
    printf("\n");
}

// 后序遍历
void postorder_node(Node * p){
    if(p == NULL) return;
    postorder_node(p->lchild);
    postorder_node(p->rchild);
    printf("%d ", p->data);
}
void postorder(Tree * tree){
    printf("postorder: ");
    postorder_node(tree->root);
    printf("\n");
}


int main(void)
{
    Tree * tree = init_tree();
    int val, ret;
    srand(time(0));
    for (int i = 0; i < RAND_OP; i++){
        val = rand() % 100 + 1; 
        ret = insert(tree, val);
        if(ret)
            printf("insert successfully --> ");
        else
            printf("%d inserted failed --> ", val);
        output(tree);
    } 
    preorder(tree);
    inorder(tree);
    postorder(tree);
    return 0;
}