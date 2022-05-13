/*
 * File: 02linklist.cpp
 * Info: 链表
 * Date: 2022-05-13
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAND_OP 10

// 定义节点结构
typedef struct ListNode {
    int data;
    struct ListNode * next;
} ListNode;
// 定义链表结构
typedef struct LinkList {
    ListNode * head;
    int length;
} LinkList;

// 初始化节点
ListNode * init_listnode(int val){
    ListNode * p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

// 初始化链表（带头节点）
LinkList * init_linklist(){
    LinkList * l = (LinkList *)malloc(sizeof(LinkList));
    l->head = init_listnode(0);
    l->length = 0;
    return l;
}

// 销毁节点
void destory_listnode(ListNode * p){
    if(p == NULL) return;
    free(p);
}

// 销毁链表（带头节点）
void destory_linklist(LinkList * l){
    if(l == NULL) return;
    ListNode * p = l->head->next, *q;
    while(p){
        q = p->next;
        destory_listnode(p);
        p = q;
    }
    free(l);
}

// 插入到l， 插入位置ind， 插入值val
// 成功为1， 失败为0
int insert(LinkList * l, int ind, int val){
    if(l == NULL) return 0;
    if(ind < 0 || ind > l->length) return 0;

    ListNode * p = l->head;
    ListNode * node = init_listnode(val);
    while (ind--)
        p = p->next;
    node->next = p->next;
    p->next = node;
    l->length++;
    return 1;
}

// 删除元素， 删除位置ind, 删除值返回到val
// 成功为1， 失败为0
int erase(LinkList * l, int ind, int * val){
    if(l == NULL) return 0;
    if(ind < 0 || ind >= l->length) return 0;
    ListNode * p = l->head, *q;
    while (ind--)
        p = p->next;
    q = p->next;
    p->next = q->next;
    *val = q->data;
    destory_listnode(q);
    l->length--;
    return 1;
}


void output(LinkList * l){
    if(l == NULL) return;
    ListNode * p = l->head->next;
    printf("List[%d] = {", l->length);
    while(p){
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL}\n");
}

int main(void)
{
    LinkList * l = init_linklist();
    int op, ind, val;
    srand(time(0));

    for(int i = 0 ; i < RAND_OP; i++){
        op = rand() % 4;
        ind = (l->length == 0? 0: rand()%l->length);
        switch(op){
            case 0:
            case 1:
            case 2:
                val = rand() % 100 + 1;
                if(insert(l, ind, val))
                    printf("%d inserted at %d pos -- >", val, ind);
                else
                    printf("insert failed -- >");
                break;
            case 3:
                if(erase(l, ind, &val))
                    printf("%d deleted at pos %d --> ", val, ind);
                else
                    printf("delete failed at pos %d --> ", ind);
                break;;
        }
        output(l);
    }
    
    return 0;
}