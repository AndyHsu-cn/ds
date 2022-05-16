/*
 * File: 03queue.cpp
 * Info: 循环队列
 * Date: 2022-05-16
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INIT_SIZE 20
#define RAND_OP 20

// 结构定义
typedef struct Queue{
    int * data;
    int head, tail;
    int length;         // 最大长度
    int cnt;            // 当前已使用长度
} Queue;

// 初始化循环队列，最大长度为n
Queue * init(int n){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->head = q->tail = 0;
    q->length = n;
    q->cnt = 0;
    return q;
}

// 销毁循环队列
void clear(Queue * q){
    if(q == NULL) return ;
    free(q->data);
    free(q);
}

// 判断是否空
int is_empty(Queue * q){
    if(q == NULL) return 0;
    return (q->cnt == 0);
}

// 判断是否满
int is_full(Queue * q){
    if(q == NULL) return 0;
    return (q->cnt == q->length);
}

// 用val返回队首元素
// 成功返回1，失败返回0
int front(Queue * q, int * val){
    if(q == NULL || q->cnt == 0) return 0;
    *val = q->data[q->head];
    return 1;
}

// 入队
// 成功返回1，失败返回0
int push(Queue * q, int val){
    if(q == NULL) return 0;
    if(is_full(q)) return 0;
    q->data[q->tail] = val;
    q->tail = (q->tail+1) % q->length;
    q->cnt++;
    return 1;
}

// 出队，并用val返回队首元素
// 成功返回1，失败返回0
int pop(Queue * q, int * val){
    if(q == NULL) return 0;
    if(is_empty(q)) return 0;
    front(q, val);
    q->head = (q->head+1) % 100;
    q->cnt--;
    return 1;
}

void output(Queue * q){
    if(q == NULL) return;
    printf("Queue[%d|%d] = {", q->cnt , q->length);
    for(int i = 0; i < q->cnt; i++){
        if(i != 0)
            printf(", ");
        printf("%d", q->data[q->head + i]);
    }
        
    printf("}\n");
}

int main()
{
    srand(time(0));
    Queue * q = init(INIT_SIZE);
    int val;

    for(int i = 0; i < RAND_OP; i++){
        int op = rand() % 4;
        switch(op){
            case 0:
            case 1:
            case 2:
                val = rand() % 100 + 1;
                if(push(q, val))
                    printf("%d pushed --> ", val);
                else
                    printf("pushed failed --> ");
                break;;
            case 3:
                if(pop(q, &val))
                    printf("%d poped --> ", val);
                else
                    printf("poped failed --> ");
                break;
        }
        output(q);
    }
    printf("Queue head pos: %d\n", q->head);

    return 0;
}