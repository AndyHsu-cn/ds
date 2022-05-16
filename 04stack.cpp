/*
 * File: 04stack.cpp
 * Info: 顺序栈
 * Date: 2022-05-16
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INIT_SIZE 20
#define RAND_OP 20

// 结构定义
typedef struct Stack{
    int * data;
    int top;
    int length;             // 最大长度
} Stack;

// 初始化顺序栈，最大长度为n
Stack * init(int n){
    Stack * s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * INIT_SIZE);
    s->top = -1;
    s->length = INIT_SIZE;
    return s;
}

// 销毁栈
void destory(Stack * s){
    if(s == NULL) return;
    free(s->data);
    free(s);
}

// 判断是否空
int is_empty(Stack * s){
    return (s->top == -1);
}

// 判断是否满
int is_full(Stack * s){
    return (s->top == s->length - 1);
}

// 用val返回栈顶元素
// 成功返回1，失败返回0
int top(Stack * s){
    if(is_empty(s)) return 0;
    return s->data[s->top];
}

// 入栈
// 成功返回1，失败返回0
int push(Stack * s, int val){
    if(s == NULL) return 0;
    if(is_full(s)) return 0;
    s->top++;
    s->data[s->top] = val;
    return 1;
}


// 出栈，并用val返回栈顶元素
// 成功返回1，失败返回0
int pop(Stack * s, int *val){
    if(s == NULL) return 0;
    if(is_empty(s)) return 0;
    *val = top(s);
    s->top--;
    return 1;
}

void output(Stack * s){
    if(s == NULL) return;
    printf("Stack[%d|%d] = {", s->top+1, s->length);
    for (int i = 0; i <= s->top; i++){
        if(i != 0)
            printf(", ");
        printf("%d", s->data[i]);
    }
    printf("}\n");   
}

int main()
{
    srand(time(0));
    Stack * s = init(INIT_SIZE);
    int val, op;

    for (int i = 0; i < RAND_OP; i++){
        op = rand() % 4;
        switch(op){
            case 0:
            case 1:
            case 2:
                val = rand() % 100 + 1;
                if(push(s, val))
                    printf("%d pushed --> ", val);
                else
                    printf("pushed failed --> ");
                break;;
            case 3:
                if(pop(s, &val))
                    printf("%d poped --> ", val);
                else
                    printf("poped failed --> ");
                break;;
        }
        output(s);
    }
    
    return 0;
}
