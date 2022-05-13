/*
 * File: 01vector.cpp
 * Info: 顺序表
 * Date: 2022-05-12
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INIT_SIZE 10
#define INC_SIZE 5
#define RAND_OP 20


typedef struct Vector{
    int * data;
    int size;           // 总长度
    int length;         // 当前长度
} Vector;

Vector * init();
int destory(Vector * vec);
int insert(Vector * vec, int ind, int val);
int erase(Vector * vec, int ind, int *val);
void output(Vector * vec);
int expand(Vector * vec);

// 初始化有INIT_SIZE个元素的顺序表
Vector * init(){
    Vector * vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * INIT_SIZE);
    vec->size = INIT_SIZE;
    vec->length = 0;
    return vec;
}

// 销毁顺序表 成功为1，失败为0
int destory(Vector * vec){
    if(vec == NULL)
        return 0;
    free(vec->data);
    free(vec);
    return 1;
}

// 插入到vec， 插入位置ind， 插入值val
// 成功为1， 失败为0
int insert(Vector * vec, int ind, int val){
    if(vec == NULL) return 0;
    if(vec->size == vec->length){
        if(!expand(vec))
            return 0;
    }
    if(ind < 0 || ind > vec->length) return 0;

    for(int i = vec->length; i > ind; i--)
        vec->data[i] = vec->data[i-1];
    vec->data[ind] = val;
    vec->length++;
    return 1;
}

// 删除元素， 删除位置ind, 删除值返回到val
// 成功为1， 失败为0
int erase(Vector * vec, int ind, int *val){
    if(vec == NULL) return 0;
    if(vec->length == 0) return 0;
    if(ind < 0 || ind >= vec->length) return 0;

    *val = vec->data[ind];
    for (int i = ind + 1; i < vec->length; i++)
        vec->data[i-1] = vec->data[i];
    vec->length--;
    return 1;
}

// 输出顺序表
void output(Vector * vec){
    printf("Vec[%d] = {", vec->length);
    for(int i = 0; i < vec->length; i++){
        if(i != 0) printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("}\n");
}

int expand(Vector * vec){
    int new_size = vec->size + INC_SIZE;
    int * new_data = (int *)realloc(vec->data, new_size * sizeof(int));
    if(new_data == NULL)
        return 0;
    vec->data = new_data;
    vec->size = new_size;
    return 1;
}

int main()
{
    srand(time(0));
    Vector *vec = init();
    int op, ind, val;
    
    for (int i = 0; i < RAND_OP; i++){
        op = rand() % 4;
        ind =  (vec->length == 0 ? 0: rand()%vec->length);
        
        switch (op)
        {
        // 以75%的概率生成插入操作，25%的概率生成删除操作
        case 0:
        case 2:
        case 3:
            val = rand() % 100 + 1;
            if(insert(vec, ind, val)) {
                printf("%d inserted at pos %d --> ", val, ind);
            }else
                printf("insert failed -- >");
            break;
        case 1:
            if(erase(vec, ind, &val)) {
                printf("%d deleted at pos %d --> ", val, ind);
            }else
                printf("delete failed at pos %d --> ", ind);
            break;;
        }
        output(vec);
    }

    return 0;
}